
#include <cstdio>
#include <iostream>
//#include "opencv2/opencv.hpp"
#ifdef _WIN32
#include <io.h>
#elif defined(__APPLE__)
#include <unistd.h>
#endif
#include "opencv_first.h"

#ifndef TEST_IMG
#define TEST_IMG "Default Value"
#endif

using namespace std;
//using namespace cv;
#include <iostream>

int main(){
    std::cout << "Hello, test" << std::endl;
//    char *file = R"(D:\000\0FFmpeg\OcrLiteNcnn-1.8.1\images\1.jpg)";
    char *file = TEST_IMG;
//    char *file = R"(\test\img.png)";
    printf("%s\n", TEST_IMG);
    if (access(file, F_OK) == 0)
    {
        printf("img.png exists.\n");
    }
    cout << "Hellow opencv " << endl;

    openImgByOpenCV(file);
//    test();
//    Mat img = imread(file);
//    if (img.empty()) {
//        cout << "Error" << endl;
//        return -1;
//    }
    return 0;
}
