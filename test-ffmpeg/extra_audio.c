#include <stdio.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/log.h>

//定义一个AVClass结构体的实例名为extraAContext
static const AVClass extraAContext = {
        .class_name = "ExtraAudio",
        .item_name  = av_default_item_name,
        .version    = LIBAVUTIL_VERSION_INT,
};

struct {
    const AVClass *av_class;
} extAudCtx;

int extra_audio(char *src_media, char *dest_audio) {
    extAudCtx.av_class = &extraAContext;
    av_log_set_level(AV_LOG_DEBUG);
//    av_log(&extAudCtx, AV_LOG_INFO, "avformat_configurations: \n %s", avformat_configuration());
    av_log(&extAudCtx, AV_LOG_VERBOSE, "av_version_info : %s\n", av_version_info());
    av_log(&extAudCtx, AV_LOG_VERBOSE, "avcodec_version : %d\n", avcodec_version());
    av_log(&extAudCtx, AV_LOG_VERBOSE, "avformat_version: %d\n", avformat_version());
    av_log(&extAudCtx, AV_LOG_VERBOSE, "avutil_version  : %d\n", avutil_version());
    AVFormatContext *pFmtCtx = NULL;
    int rest = -1;
//    打开多媒体文件
    if ((rest = avformat_open_input(&pFmtCtx, src_media, NULL, NULL)) < 0) {
        av_log(&extAudCtx, AV_LOG_ERROR, "avformat_open_input error: %s \n", av_err2str(rest));
        return -1;
    }
//    2, 从多媒体中找到音频流
    int aud_idx = av_find_best_stream(pFmtCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
    if (aud_idx < 0) {
        av_log(&extAudCtx, AV_LOG_ERROR, "av_find_best_stream error %d", aud_idx);
        goto _release;
    }
//    3, 打开目的文件的上下文
    AVFormatContext *pOFmtCtx = avformat_alloc_context();
    if (!pOFmtCtx) {
        av_log(&extAudCtx, AV_LOG_ERROR, "No memory");
        goto _release;
    }
    const AVOutputFormat *pOFormat = av_guess_format(NULL, dest_audio, NULL);
    pOFmtCtx->oformat = pOFormat;
//    4，为目的文件创建一个新的音频流
    AVStream *pOStream = avformat_new_stream(pOFmtCtx, NULL);
//    5，设置目的音频流的参数
    AVStream *pStream = pFmtCtx->streams[aud_idx];
    avcodec_parameters_copy(pOStream->codecpar, pStream->codecpar);
    pOStream->codecpar->codec_tag = 0;//根据多媒体文件自动设置编解码器

//   将AVFormatContext和文件绑定
    if ((rest = avio_open2(&pOFmtCtx->pb, dest_audio, AVIO_FLAG_WRITE, NULL, NULL)) < 0) {
        av_log(&extAudCtx, AV_LOG_ERROR, "avio_open2 error: %s \n", av_err2str(rest));
        goto _release;
    }
//    6，写多媒体文件头到目的文件
    if ((rest = avformat_write_header(pOFmtCtx, NULL)) < 0) {
        av_log(&extAudCtx, AV_LOG_ERROR, "avformat_write_header error: %s \n", av_err2str(rest));
        goto _release;
    }
//    7，从源文件中读取音频数据到目的文件
    AVPacket pkt;
    while (av_read_frame(pFmtCtx, &pkt) >= 0) {
        if (pkt.stream_index == aud_idx) {
            pkt.pts = av_rescale_q_rnd(pkt.pts, pStream->time_base, pkt.time_base,
                                       (AV_ROUND_NEAR_INF | AV_CODEC_ID_VMIX));
            pkt.dts = pkt.pts;
            pkt.duration = av_rescale_q(pkt.duration, pStream->time_base, pkt.time_base);
            pkt.stream_index = 0;
            pkt.pos = -1;
            av_interleaved_write_frame(pOFmtCtx, &pkt);
            av_packet_unref(&pkt);
        }
    }
//    8，写多媒体文件尾到目的文件
    av_write_trailer(pOFmtCtx);
//    9，释放资源
    _release:
    if (pFmtCtx != NULL) {
        avformat_close_input(&pFmtCtx);
    }
    if (pOFmtCtx && pOFmtCtx->pb) {
        avio_close(pOFmtCtx->pb);
    }
    if (pOFmtCtx) {
        avformat_close_input(&pOFmtCtx);
    }
    return 0;
}

int _main_(int argc, char *argv[]) {
    if (argc < 2) {
        exit(-1);
    }
    return extra_audio(argv[1], argv[2]);
}
