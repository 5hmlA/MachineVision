#include <stdio.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

int main() {
    // 定义一个字符串
    char *video = "C:\\Users\\xuchuqi\\CLionProjects\\MachineVision\\test_video.mp4";
    // 使用printf输出字符串
    printf("%s\n", video);
    av_log_set_level(AV_LOG_DEBUG);
    av_log_set_level(AV_LOG_DEBUG);
//    av_log(NULL, AV_LOG_INFO, "avformat_configurations: \n %s", avformat_configuration());
    av_log(NULL, AV_LOG_VERBOSE, "av_version_info : %s\n", av_version_info());
    av_log(NULL, AV_LOG_VERBOSE, "avcodec_version : %d\n", avcodec_version());
    av_log(NULL, AV_LOG_VERBOSE, "avformat_version: %d\n", avformat_version());
    av_log(NULL, AV_LOG_VERBOSE, "avutil_version  : %d\n", avutil_version());
    AVFormatContext *pFmtCtx = NULL;
    int ret = -1;
    if ((ret = avformat_open_input(&pFmtCtx, video, NULL, NULL)) < 0) {
        av_log(pFmtCtx, AV_LOG_ERROR, "avformat_open_input error: %s \n", av_err2str(ret));
        exit(-1);
    }
    av_dump_format(pFmtCtx, 0, video, 0);
    _release:
    if (pFmtCtx != NULL) {
        avformat_close_input(&pFmtCtx);
    }
    return 0;
}
