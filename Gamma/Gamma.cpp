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

//课前准备1-老师
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

int drawSimpleHist(cv::Mat & histMat, float * srcHist)
{
	int h = 100;
	int bin = 3;
	histMat.create(100, 256 * bin, CV_8UC1);
	histMat = Scalar(255);

	float maxVal = *std::max_element(srcHist, srcHist + 256);

	for (int i = 0; i < 256; i++) {
		Rect binRect;
		binRect.x = i * bin;
		float height_i = (float)h*srcHist[i] / maxVal;
		binRect.height = (int)height_i;
		binRect.y = h - binRect.height;
		binRect.width = bin;
		rectangle(histMat, binRect, CV_RGB(50, 50, 50), -1);
	}

	return 0;
}

int calcSimpleHist(const cv::Mat src, float * dstHist)
{

	//输入必为灰度图
	if (src.type() != CV_8UC1) {
		return -1;
	}

	memset(dstHist, 0, sizeof(float) * 256);
	int height = src.rows;
	int width = src.cols;
	//指针遍历
	for (int k = 0; k < height; k++)
	{
		// 获取第k行的首地址
		const uchar* inData = src.ptr<uchar>(k);
		//uchar* outData = dstImg.ptr<uchar>(k);
		//处理每个像素
		for (int i = 0; i < width; i++)
		{
			int gray = inData[i];
			dstHist[gray]++;
		}
	}

	//直方图归一化
	float norm = height * width;
	for (int n = 0; n < 256; n++) {
		dstHist[n] = dstHist[n] / norm;
	}


	return 0;
}

int calcSimpleHistWithMask(const cv::Mat src, const cv::Mat mask, float * dstHist)
{
	//输入必为灰度图
	if (src.type() != CV_8UC1 ||
		mask.type() != CV_8UC1 ||
		src.size() != mask.size()) {
		return -1;
	}

	memset(dstHist, 0, sizeof(float) * 256);
	int height = src.rows;
	int width = src.cols;

	//指针遍历
	float norm = 0;
	for (int k = 0; k < height; k++)
	{
		// 获取第k行的首地址
		const uchar* inData = src.ptr<uchar>(k);
		const uchar* maskData = mask.ptr<uchar>(k);
		//处理每个像素
		for (int i = 0; i < width; i++)
		{
			int gray = inData[i];
			int maskFlag = maskData[i];
			if (maskFlag == 255) {
				dstHist[gray]++;
				norm++;
			}
		}
	}

	//直方图归一化
	for (int n = 0; n < 256; n++) {
		dstHist[n] = dstHist[n] / norm;
	}

	return 0;
}
//*
int gammaMain()
{

	cv::Mat srcMat = imread("E:\\10\\tlp.jpg", 0);
	cv::Mat dstMat;

	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return -1;
	}

	float gamma = 0.5;

	gammaCorrection(srcMat, dstMat, gamma);

	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);

	destroyAllWindows();

	return 0;
}//*/

///*
int equalizeMain()
{
	cv::Mat srcMat = imread("E:\\9\\hogTemplate.jpg", 0);
	cv::Mat dstMat;

	equalizeHist(srcMat, dstMat);

	//绘制直方图
	float srcHist[256];
	float dstHist[256];

	cv::Mat srcHistMat;
	cv::Mat dstHistMat;

	calcSimpleHist(srcMat, srcHist);
	calcSimpleHist(dstMat, dstHist);
	drawSimpleHist(srcHistMat, srcHist);
	drawSimpleHist(dstHistMat, dstHist);

	imshow("srcMat", srcMat);
	imshow("dstMat", dstMat);
	imshow("srcHistMat", srcHistMat);
	imshow("dstHistMat", dstHistMat);

	waitKey(0);

	destroyAllWindows();

	return 0;

}//*/

///*
int main()
{
	//开始计时
	double start = static_cast<double>(cvGetTickCount());

	//gamma矫正演示
	gammaMain();

	//直方图均衡演示
	//equalizeMain();

	//结束计时
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//显示时间
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//等待键盘响应，按任意键结束程序
	system("pause");
	return 0;
}
//*/