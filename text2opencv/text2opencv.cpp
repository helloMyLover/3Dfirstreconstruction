
/*3Dreconstruction
2016.3.7 加入SIFT算法识别图像特征
*/
#include "stdafx.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	//cvNamedWindow("src",1);
	Mat input1=imread("pic//IMG_5595.jpg");
	Mat input2=imread("pic//IMG_5594.jpg");
	Mat temp=input1;
	if(!input1.data || !input2.data)
	{
		printf("Read image data Failure\n");
		return 1;
	}
	namedWindow("src",CV_WINDOW_AUTOSIZE);


	cv::Size picSize;
	picSize.height=80;
	picSize.width=80;

	resize(input1,input1,picSize);
	resize(input2,input2,picSize);

	//resizeWindow("src",50,80);
	cvWaitKey(0);
	while( true )
	{
		int c;
		c=waitKey(10);
		if( (char)c ==27)
		{
			break;
		}
		else if((char)c=='u')
		{
			pyrUp(temp,input1,Size(temp.cols*2,temp.rows*2));
			printf("** Zoom In : Image*2\n");
		}
		else if((char)c=='d')
		{
			pyrDown(temp,input1,Size(temp.cols/2,temp.rows/2));
			printf("** Zoom In : Image/2\n");
		}
		imshow("src",input1);
		temp=input1;
	}
	cvWaitKey(0);
	//threshold(input,img_threshold,60,255,CV_THRESH_BINARY_INV);


	//	Mat img_threshold;
	//Mat img_contours;
	//img_threshold.copyTo(img_contours);
	//vector<vector<Point>> contours;
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

