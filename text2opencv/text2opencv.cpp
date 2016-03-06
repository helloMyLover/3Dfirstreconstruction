
#include "stdafx.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cvNamedWindow("src",1);
	Mat input=imread("pic//IMG_5595.jpg");
	Mat img_threshold;
	cv::Size picSize;
	picSize.height=100;
	picSize.width=150;
	resizeWindow("src",150,100);
	resize(input,input,picSize);
	//threshold(input,img_threshold,60,255,CV_THRESH_BINARY_INV);
	imshow("src",input);
	cvWaitKey(0);
	Mat img_contours;
	img_threshold.copyTo(img_contours);
	vector<vector<Point>> contours;
//	findContours(img_contours,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
	//vector<int> test_data;
	//vector<int>::iterator check;
	//for( check = test_data.begin() ; check != test_data.end() ; check ++ )
	//{
	//	
	//}
	return 0;
}

bool verifySize(Mat r)
{                                                  
	float aspect=45.0f/77.0f;
	float charAspect=(float)r.cols/(float)r.rows;
	float error=0.35;
	float minHeight=15;
	float maxHeight=28;

	float minAspect   =0.2;
	float maxAspect   =aspect+aspect*error;
	float area        =countNonZero(r);
	float bbArea      =r.rows*r.cols;
	float percPixels  =area/bbArea;

	if(percPixels<0.8 && charAspect >minAspect && charAspect < maxAspect && r.rows >= minHeight && r.rows <= maxHeight)
	{
		return true;
	}
	else
		return false;
}

