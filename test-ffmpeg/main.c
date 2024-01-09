#include <stdio.h>
#include "extra_audio.h"
#include "extra_video.h"
#include "convert_video.h"

int extra_video(char *src_media, char *dest_video);

int convert_video(char *src_media, char *dest_video);

int main(int argc, char* argv[]) {
    // 定义一个字符串
    char *video = "C:\\Users\\xuchuqi\\CLionProjects\\MachineVision\\test_video.mp4";
    // 使用printf输出字符串
    printf("%s\n", video);
//    extra_audio(video,"1.aac");
//    extra_video(video,"1.h264");
    convert_video(video,"1.mov");
    return 0;
}
