#include <stdio.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

int main() {
    // 定义一个字符串
    char *video = "C:\\Users\\xuchuqi\\CLionProjects\\MachineVision\\test_video.mp4";
    // 使用printf输出字符串
    printf("%s\n", video);
    av_log_set_level(AV_LOG_DEBUG);
//    av_log(NULL, AV_LOG_INFO, "avformat_configurations: \n %s", avformat_configuration());

//test_video.mp4
//
    AVFormatContext *avFormatContext = NULL;
    int ret = 0;
    if ((ret = avformat_open_input(&avFormatContext, video, NULL, NULL))) {
        av_log(NULL, AV_LOG_ERROR, "%s\n", av_err2str(ret));
        exit(-1);
    }
    printf("------------------------");
    free(avFormatContext);
    return 0;
}
