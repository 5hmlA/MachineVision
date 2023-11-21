
#include <cstdio>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <io.h>

using namespace std;
using namespace cv;
#include <iostream>

int main(){
    std::cout << "Hello, test" << std::endl;
//    char *file = R"(D:\000\0FFmpeg\OcrLiteNcnn-1.8.1\images\1.jpg)";
    char *file = "img.png";
    if (access(file, F_OK) == 0)
    {
        printf("1.txt exists.\n");
    }
    Mat img = imread(file);
    if (img.empty()) {
        cout << "Error" << endl;
        return -1;
    }
    return 0;
}
