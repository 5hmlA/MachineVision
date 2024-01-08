#include <stdio.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include "extra_audio.h"

int main(int argc, char* argv[]) {
    // 定义一个字符串
    char *video = "C:\\Users\\xuchuqi\\CLionProjects\\MachineVision\\test_video.mp4";
    // 使用printf输出字符串
    printf("%s\n", video);
    extra_audio(video,"1.acc");
    return 0;
}
