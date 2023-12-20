//
// Created by xuchuqi on 2023/12/19.
//

#include <string>
#include <iostream>
#include "../opencv_first.h"
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>

void openImgByOpenCV(const std::string &path) {
    std::cout << "out put from openImgByOpenCV: " << path;
    cv::Mat image = cv::imread(path);

    // 检查是否成功读取图片
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image" << std::endl;
        return;
    }

    // 创建一个窗口来显示图片
    cv::namedWindow("OpenCV Image", cv::WINDOW_NORMAL);

    // 在窗口中显示图片
    cv::imshow("OpenCV Image", image);

    // 等待用户按下任意键
    cv::waitKey(0);
}

void test() {
    std::cout << "out put from openImgByOpenCV: ";
}