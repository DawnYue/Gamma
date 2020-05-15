#include <iostream>  
#include <opencv2\core\core.hpp>  
#include <opencv2\highgui\highgui.hpp>  
#include <opencv2\imgproc\imgproc.hpp>  
#include<cmath>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>
#include <vector>
#include "cv.h"
using namespace cv;
using namespace std;

//练习2
int main()
{
	cv::Mat srcMat = imread("E:\\11\\etest.jpg");
	cv::Mat dstMat;

	//0.输入图像，类型是 8位单通道
	//1.输出图像，与输入同样尺寸同样类型
	if (srcMat.type() == CV_8UC1) {
		equalizeHist(srcMat, dstMat);
	}
	else if (srcMat.type() == CV_8UC3) {
		Mat channel[3];
		Mat out[3];
		split(srcMat, channel);

		for (int i = 0; i < 3; i++) {
			equalizeHist(channel[i], out[i]);
		}
		merge(out, 3, dstMat);
	}

	cv::Mat srcHistMat;
	cv::Mat dstHistMat;

	imshow("srcMat", srcMat);
	imshow("dstMat", dstMat);

	waitKey(0);

	destroyAllWindows();

	return 0;
}