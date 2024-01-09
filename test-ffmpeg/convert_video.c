#include <stdio.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/log.h>

//定义一个AVClass结构体的实例名为extraAContext
static const AVClass ConvertContext = {
        .class_name = "ExtraAudio",
        .item_name  = av_default_item_name,
        .version    = LIBAVUTIL_VERSION_INT,
};

struct {
    const AVClass *av_class;
} covtCtx;

void log_duration(int64_t duration_sec) {
    int hour, minute, sec;
    hour = duration_sec / 3600;
    minute = duration_sec % 3600 / 60;
    sec = duration_sec % 60;
    av_log(&covtCtx, AV_LOG_VERBOSE, "media total time: %d:%d:%d \n", hour, minute, sec);
}

// 1 avformat_open_input 打开输入流并读取标头。填充到pFmtCtx数据中，编解码器未打开
// 2 avformat_alloc_output_context2 为指定输出文件格式分配 AVFormatContext，会自动根据文件格式生成对应的AVOutputFormat
// 3 pOFmtCtx->pb 关联到具体文件
// 4 遍历所有流，记录需要的流的index,并把对应输入文件的各个流的codepar复制到对应的pOFmtCtx输出上下文总的各个流的codecpar数据
// 5 写入信息头, 必须在更新pOFmtCtx的所有AVStream的codecpar之后才可以执行，否则执行失败
// 6 复制音/视/字幕流  av_read_frame()>=0,av_packet_rescale_ts,av_interleaved_write_frame,av_packet_unref
// 7 av_write_trailer 将流预告片写入输出媒体文件
int convert_video(char *src_media, char *dest_video) {
    covtCtx.av_class = &ConvertContext;
    av_log_set_level(AV_LOG_DEBUG);
//    av_log(&covtCtx, AV_LOG_INFO, "avformat_configurations: \n %s", avformat_configuration());
    av_log(&covtCtx, AV_LOG_VERBOSE, "av_version_info : %s\n", av_version_info());
    av_log(&covtCtx, AV_LOG_VERBOSE, "avcodec_version : %d\n", avcodec_version());
    av_log(&covtCtx, AV_LOG_VERBOSE, "avformat_version: %d\n", avformat_version());
    av_log(&covtCtx, AV_LOG_VERBOSE, "avutil_version  : %d\n", avutil_version());

    AVFormatContext *pFmtCtx = NULL;
    AVFormatContext *pOFmtCtx = NULL;
    int *strm_map = NULL;
    int rest = 0;
    if ((rest = avformat_open_input(&pFmtCtx, src_media, NULL, NULL)) < 0) {
        av_log(&covtCtx, AV_LOG_ERROR, "avformat_open_input error: %s\n", av_err2str(rest));
        return -1;
    }

    av_dump_format(pFmtCtx, 0, src_media, 0);
    av_log(&covtCtx, AV_LOG_VERBOSE, "src media path=%s \n", pFmtCtx->url);
//    打印流数量
    av_log(&covtCtx, AV_LOG_VERBOSE, "src media stream number=%d \n", pFmtCtx->nb_streams);
//    打印码率
    av_log(&covtCtx, AV_LOG_VERBOSE, "src media average ratio:%lld kbps\n", (int64_t) (pFmtCtx->bit_rate / 1024));
    int duration_sec, hour, minute, sec;
//    ctx->duration的单位是微妙，先转为秒
    duration_sec = (pFmtCtx->duration) / AV_TIME_BASE;
    hour = duration_sec / 3600;
    minute = duration_sec % 3600 / 60;
    sec = duration_sec % 60;
    av_log(&covtCtx, AV_LOG_VERBOSE, "media total time: %d:%d:%d \n", hour, minute, sec);

    // 1 avformat_open_input 打开输入流并读取标头。填充到pFmtCtx数据中，编解码器未打开
    // 2 avformat_alloc_output_context2 为指定输出文件格式分配 AVFormatContext，会自动根据文件格式生成对应的AVOutputFormat
    // 3 pOFmtCtx->pb 关联到具体文件
    // 4 遍历所有流，记录需要的流的index,并把对应输入文件的各个流的codepar复制到对应的pOFmtCtx输出上下文总的各个流的codecpar数据
    // 5 写入信息头, 必须在更新pOFmtCtx的所有AVStream的codecpar之后才可以执行，否则执行失败
    // 6 复制音/视/字幕流  av_read_frame()>=0,av_packet_rescale_ts,av_interleaved_write_frame,av_packet_unref
    // 7 av_write_trailer 将流预告片写入输出媒体文件

    if ((rest = avformat_alloc_output_context2(&pOFmtCtx, NULL, NULL, dest_video)) < 0) {
        av_log(&covtCtx, AV_LOG_ERROR, "avformat_alloc_output_context2 error: %s\n", av_err2str(rest));
        goto _release;
    }

    if (!pOFmtCtx) {
        av_log(&covtCtx, AV_LOG_ERROR, "avformat_alloc_output_context2 return NULL: NO MEMORY\n");
        goto _release;
    }

    //pOFmtCtx->pb 关联到具体文件
    if ((rest = avio_open2(&pOFmtCtx->pb, dest_video, AVIO_FLAG_WRITE, NULL, NULL)) < 0) {
        av_log(&covtCtx, AV_LOG_ERROR, "avio_open2 error: %s\n", av_err2str(rest));
        goto _release;
    }

    //记录需要的音/视/字幕流的index
    strm_map = av_calloc(pFmtCtx->nb_streams, sizeof(int));
    if (!strm_map) {
        av_log(&covtCtx, AV_LOG_ERROR, "avformat_alloc_output_context2 return NULL: NO MEMORY\n");
        goto _release;
    }

    int cut_indx = 0;
    for (int i = 0; i < pFmtCtx->nb_streams; ++i) {
        AVStream *pInStream = pFmtCtx->streams[i];
        enum AVMediaType codec_type = pInStream->codecpar->codec_type;
        if (codec_type != AVMEDIA_TYPE_AUDIO && codec_type != AVMEDIA_TYPE_VIDEO && codec_type != AVMEDIA_TYPE_SUBTITLE) {
            strm_map[i] = -1;
            continue;
        }
        AVStream *pOtStream = avformat_new_stream(pOFmtCtx, NULL);
        if (!pOtStream) {
            av_log(&covtCtx, AV_LOG_ERROR, "avformat_new_stream error: No memory\n");
            continue;
        }
        avcodec_parameters_copy(pOtStream->codecpar, pInStream->codecpar);
        pOtStream->codecpar->codec_tag = 0;//让ffmpeg根据多媒体文件自动设置编解码器
        strm_map[i] = cut_indx++;
    }

    //写入信息头, 必须在更新pOFmtCtx的所有AVStream的codecpar之后才可以执行，否则执行失败
    if ((rest = avformat_write_header(pOFmtCtx, NULL)) < 0) {
        av_log(&covtCtx, AV_LOG_ERROR, "avformat_write_header error: %s\n", av_err2str(rest));
        goto _release;
    }

    //复制音/视/字幕流
    AVPacket pkt_box;
    while (av_read_frame(pFmtCtx, &pkt_box) >= 0) {
        //具体某个流复制
        //读取出所有流的帧数据
        int i_strm_indx = pkt_box.stream_index;
        int o_strm_indx = strm_map[i_strm_indx];
        if (o_strm_indx == -1) {
            av_packet_unref(&pkt_box);
            continue;
        }
        //纠正 给输出数据的 AVPacket 的stream_index
        pkt_box.stream_index = o_strm_indx;
        av_packet_rescale_ts(&pkt_box, pFmtCtx->streams[i_strm_indx]->time_base, pOFmtCtx->streams[o_strm_indx]->time_base);
        pkt_box.pos = 0;
        //将数据包写入输出媒体文件，确保正确交错
        av_interleaved_write_frame(pOFmtCtx, &pkt_box);
        av_packet_unref(&pkt_box);
    }

    //将流预告片写入输出媒体文件
    av_write_trailer(pOFmtCtx);

    _release:
    if (strm_map) {
        av_free(strm_map);
    }
    if (pFmtCtx) {
        avformat_close_input(&pFmtCtx);
    }
    if (pOFmtCtx) {
        avformat_close_input(&pOFmtCtx);
    }
    if (pOFmtCtx && pOFmtCtx->pb) {
        avio_close(pOFmtCtx->pb);
    }
    return 0;
}
