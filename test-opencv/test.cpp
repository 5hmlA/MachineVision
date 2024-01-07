
#include <cstdio>
#include <iostream>
//#include "opencv2/opencv.hpp"
#include <io.h>
#include "opencv_first.h"

using namespace std;
//using namespace cv;
#include <iostream>

int main(){
    std::cout << "Hello, test" << std::endl;
//    char *file = R"(D:\000\0FFmpeg\OcrLiteNcnn-1.8.1\images\1.jpg)";
    char *file = R"(C:\Users\xuchuqi\CLionProjects\MachineVision\test-opencv\img.png)";
//    char *file = R"(\test\img.png)";
    if (access(file, F_OK) == 0)
    {
        printf("img.png exists.\n");
    }
    cout << "Error " << endl;

    std::string path = file;

    openImgByOpenCV(path);
//    test();
//    Mat img = imread(file);
//    if (img.empty()) {
//        cout << "Error" << endl;
//        return -1;
//    }
    return 0;
}
