#ifndef MACHINEVISION_WINGS_H
#define MACHINEVISION_WINGS_H

#include <locale.h>
// 定义一个宏，用于设置本地化信息为 "zh-CN.UTF-8"
#define SET_CHINESE_LOCALE() setlocale(LC_ALL, "zh-CN.UTF-8")
#define PI 3.14159265358979323846
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#include <assert.h>

#define ASSERT(condition) assert(condition)
#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

#include <stdio.h>

#define LOGE(tag, fmt, ...) fprintf(stderr, __FILE__":%d %s:"fmt"\n",__LINE__,tag, ##__VA_ARGS__)
#define LOGD(tag, fmt, ...) fprintf(stdout, __FILE__":%d %s:"fmt"\n",__LINE__,tag, ##__VA_ARGS__)


//<editor-fold desc="Time">
#if defined(__unix__)
#include <sys/time.h>
#elif defined(__WIN32__)
#include <sys/timeb.h>
#else
#include <time.h>
#endif

typedef long long long_time_t;

long_time_t millisecondTime() {
#if defined(__WIN32__)
    struct timeb time_buffer;
    ftime(&time_buffer);
    return time_buffer.time * 1000LL + time_buffer.millitm;
#elif defined(__unix__)
    struct timeval time_value;
    gettimeofday(&time_value, NULL);
    return time_value.tv_sec * 1000LL + time_value.tv_usec / 1000;
#else
    time_t curt_time = time(NULL);
    return curt_time * 1000LL;
#endif
}
//</editor-fold>

//<editor-fold desc="FFMPEG">
#include "libavutil/log.h"

#define AV_ERROR(ctx, fmt, ...) av_log(&ctx, AV_LOG_ERROR, __FILE__":%d "fmt"\n",__LINE__, ##__VA_ARGS__);
//</editor-fold>


#endif
//MACHINEVISION_WINGS_H

