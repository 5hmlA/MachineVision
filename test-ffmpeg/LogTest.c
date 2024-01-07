#include <stdio.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

int main() {
    // 定义一个字符串
    char myString[] = "Hello, World!";

    // 使用printf输出字符串
    printf("%s\n", myString);
    av_log_set_level(AV_LOG_DEBUG);
    av_log(NULL, AV_LOG_WARNING, "000");
    av_log(NULL, AV_LOG_INFO, "avformat_configurations: \n %s", avformat_configuration());
    return 0;
}
