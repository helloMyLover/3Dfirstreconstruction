
/*3Dreconstruction
2016.3.7 加入SIFT算法识别图像特征
*/
#include "stdafx.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <opencv2\features2d\features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
void changeSizetoSame(Mat & inputImage);

int _tmain(int argc, _TCHAR* argv[])
{
//	Ptr<SIFT> detector = SIFT::create();
	Mat input1=imread("pic//IMG_5597.jpg",IMREAD_GRAYSCALE );
	Mat input2=imread("pic//IMG_5598.jpg");
	Mat descriptors;
	vector<KeyPoint> keypoints;
	//initModule_nonfree();
	if(!input1.data || !input2.data)
	{
		printf("Read image data Failure\n");
		return 1;
	}
	//changeSizetoSame(input1);
	imshow("src",input2);
	cvWaitKey(0);
	cv::Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
	//threshold(input,img_threshold,60,255,CV_THRESH_BINARY_INV);

	std::vector<KeyPoint> keypoints_1, keypoints_2;    
  f2d->detect( input1, keypoints_1 );
  f2d->detect( input2, keypoints_2 );

  //-- Step 2: Calculate descriptors (feature vectors)    
  Mat descriptors_1, descriptors_2;    
  f2d->compute( input1, keypoints_1, descriptors_1 );
  f2d->compute( input2, keypoints_2, descriptors_2 );

  //-- Step 3: Matching descriptor vectors using BFMatcher :
  BFMatcher matcher;
  std::vector< DMatch > matches;
  matcher.match( descriptors_1, descriptors_2, matches );
//	Ptr<Feature2D> sift = Algorithm::create<Feature2D>("Feature2D.SIFT");
	destroyAllWindows();
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

void changeSizetoSame(Mat & inputImage)
{
	Mat tempImage=inputImage;
	if(tempImage.rows != 437 ||tempImage.cols !=656 )
	{
		resize(tempImage,inputImage,Size(437,656));
	}
	if(inputImage.channels() != 1)
	{
		cvtColor(inputImage,inputImage,CV_BGR2GRAY);
	}
}

void pyramidSize(const Mat inputImage,Mat & outImage)
{
	Mat temp=inputImage;
	int c;
	c=waitKey(10);
	if( (char)c ==27 || (char)c =='q')
	{
		return;
	}
	else if((char)c=='u')
	{
		pyrUp(temp,outImage,Size(temp.cols*2,temp.rows*2));
		printf("** Zoom In : Image*2\n");
	}
	else if((char)c=='d')
	{
		pyrDown(temp,outImage,Size(temp.cols/2,temp.rows/2));
		printf("** Zoom In : Image/2\n");
	}
	imshow("src",outImage);
	temp=outImage;
	destroyWindow("src");
}



