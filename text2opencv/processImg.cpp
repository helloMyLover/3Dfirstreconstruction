#include "StdAfx.h"
#include "processImg.h"


//在同一窗口显示多幅图片
void imshowMany( const vector<Mat>& _imgs)
{
 int nImg = (int)_imgs.size();
  
 Mat dispImg;
 int size;
 int x, y;
 // w - Maximum number of images in a row 
 // h - Maximum number of images in a column 
 int w, h;
 // scale - How much we have to resize the image
 float scale;
 int max;
 if (nImg <= 0) 
 {
  printf("Number of arguments too small....\n");
  return;
 }
 else if (nImg > 12)
 {
  printf("Number of arguments too large....\n");
  return;
 }
  
 else if (nImg == 1)
 {
  w = h = 1;
  size = 300;
 }
 else if (nImg == 2)
 {
  w = 2; h = 1;
  size = 300;
 }
 else if (nImg == 3 || nImg == 4)
 {
  w = 2; h = 2;
  size = 300;
 }
 else if (nImg == 5 || nImg == 6)
 {
  w = 3; h = 2;
  size = 200;
 }
 else if (nImg == 7 || nImg == 8)
 {
  w = 4; h = 2;
  size = 200;
 }
 else
 {
  w = 4; h = 3;
  size = 150;
 }
 dispImg.create(Size(100 + size*w, 60 + size*h), CV_8UC3);
 for (int i= 0, m=20, n=20; i<nImg; i++, m+=(20+size))
 {
  x = _imgs[i].cols;
  y = _imgs[i].rows;
  max = (x > y)? x: y;
  scale = (float) ( (float) max / size );
  if (i%w==0 && m!=20)
  {
   m = 20;
   n += 20+size;
  }
  Mat imgROI = dispImg(Rect(m, n, (int)(x/scale), (int)(y/scale)));
  resize(_imgs[i], imgROI, Size((int)(x/scale), (int)(y/scale)));
 }
 imshow("lily", dispImg);
}


