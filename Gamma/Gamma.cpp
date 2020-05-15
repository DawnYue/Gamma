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

//练习3
int gammaCorrection(cv::Mat srcMat, cv::Mat & dstMat, float gamma)
{

	//本函数只处理单通道图像
	if (srcMat.channels() != 1)return -1;

	//建立查询表
	unsigned char lut[256];
	for (int i = 0; i < 256; i++)
	{
		//saturate_cast，防止像素值溢出，如果值<0,则返回0，如果大于255，则返回255
		lut[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
	}

	srcMat.copyTo(dstMat);

	MatIterator_<uchar> it, end;
	for (it = dstMat.begin<uchar>(), end = dstMat.end<uchar>(); it != end; it++) {
		*it = lut[(*it)];
	}

	return 0;
}

int gammaMain()
{

	cv::Mat srcMat = imread("E:\\11\\gtest.jpg", 0);
	cv::Mat dstMat;

	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return -1;
	}

	float gamma = 0.45;

	gammaCorrection(srcMat, dstMat, gamma);

	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
int main()
{
	//开始计时
	double start = static_cast<double>(cvGetTickCount());
	//gamma矫正演示
	gammaMain();
	//结束计时
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//显示时间
	cout << "processing time:" << time / 1000 << "ms" << endl;
	//等待键盘响应，按任意键结束程序
	system("pause");
	return 0;
}
