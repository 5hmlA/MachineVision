#include <stdio.h>
#include <time.h>
#include <libavutil/avutil.h>
#include <libavformat/avformat.h>
#include "extra_audio.h"
#include "extra_video.h"
#include "convert_video.h"
#include "wings.h"

int extra_video(char *src_media, char *dest_video);

int convert_video(char *src_media, char *dest_video);

int main(int argc, char* argv[]) {
    // 定义一个字符串
    char *video = TEST_VIDEO;
    // 使用printf输出字符串
    printf("%s\n", video);
    printf("%s\n", MY_TEST_VIDEO);
    printf("%s\n", av_version_info());
    printf("%s\n", avformat_configuration());
//    extra_audio(video,"1.aac");
    extra_video(video,"1.h264");
//    convert_video(video,"1.mov");
    return 0;
}
