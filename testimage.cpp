//THIS CODE IS USED TO GENERATE A 3D MODEL VIEW OF A SIMPLE OBJECT GIVEN ITS FRONT, TOP AND SIDE VIEWS.


#include "stdafx.h"
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
//#include<opencv2/imgproc/imgproc.hpp>                            //INCLUDED FOR CANNY



using namespace std;
using namespace cv;


int main()
{
	Mat image;
	image = imread("E:\\test_fv.jpg");    //THIS IS THE INPUT IMAGE, THAT IS, THE FRONT, TOP AND SIDE VIEW
	Mat img2(image.rows, image.cols, CV_8UC1, Scalar(255));     //BINARY
	Mat img(image.rows, image.cols, CV_8UC1, Scalar(255));      //FRONT_VIEW OUTPUT

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (0.33*(image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2])>128)
				img2.at<uchar>(i, j) = 255;
			else
				img2.at<uchar>(i, j) = 0;
		}
	}

	int p = 0;
	
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (img2.at<uchar>(i, j) ==0)
			{
				//img.at<uchar>(i, j) = 128;
				for (p = 0; ((i - 0.707*p) >= 1) && ((j + 0.707*p) <= image.cols - 1); p++)
				{
					img.at<uchar>(i - 0.707*p, j + 0.707*p) = 128;
				}

				
			}
		}
	}


	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (img2.at<uchar>(i, j) == 0)
			{
				;// img.at<uchar>(i, j) = 0;
			}
		}
	}


	/************************************************************************************************/
	/************************************************************************************************/
	
	int a = 0, b = 0;
	Mat img3(image.rows, image.cols, CV_8UC1, Scalar(255));             //SIDE_VIEW OUTPUT
	for (int j = 0; j < img.cols; j++)
	{
		for (int i = 0; i < img.rows; i++)
		{
			if (img2.at<uchar>(i, j) == 0)
			{
				a = j;
				break;
			}
		}
	 if (a!=0)
			break;

	}
	
	//cout << a;

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			int l = j - a;
			if (img2.at<uchar>(i, j) == 0)
			{
				if (((i - 0.707*l) >= 0) && ((j - 0.293*l) >= 0))
				{
					img3.at<uchar>((i - 0.707*l), (j - 0.293*l)) = 0;
				}
			}
		}
	}

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (img3.at<uchar>(i, j) == 0)
			{
				for (int h = j; h < img.cols; h++)
					img3.at<uchar>(i, h) = 75;
			}
		}
	}

	Mat img4(img.rows, img.cols, CV_8UC1, Scalar(255));
	
	/********************************************************************************************************/
	/********************************************************************************************************/


	Mat img5(image.rows, image.cols, CV_8UC1, Scalar(255));             //TOP_VIEW OUTPUT
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (img2.at<uchar>(i, j) == 0)
			{
				b = i;
				break;
			}
		}
		if (b != 0)
			break;

	}

	//cout << b;

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			int m = i - b;
			if (img2.at<uchar>(i, j) == 0)
			{
				if (((i-1.707*m) >= 0) && ((j+0.707*m) <img.cols))
				{
					img5.at<uchar>((i - 1.707*m), (j + 0.707*m)) = 0;
				}
			}
		}
	}

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (img5.at<uchar>(i, j) == 0)
			{
				for (int g = i; g < img.rows; g++)
					img5.at<uchar>(g, j) = 75;
			}
		}
	}

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (img.at<uchar>(i, j) != 255 && img3.at<uchar>(i, j) != 255 && img5.at<uchar>(i,j)!=255)
				img4.at<uchar>(i, j) = 120;
		}
	}


	namedWindow("Frame", WINDOW_AUTOSIZE);
	imshow("Frame", img);
	namedWindow("Frame2", WINDOW_AUTOSIZE);
	imshow("Frame2", img3);
	namedWindow("Frame3", WINDOW_AUTOSIZE); // THIS IS THE 3D MODEL OUTPUT IMAGE, CUBE IN THIS CASE.
	imshow("Frame3", img4);
	namedWindow("Frame4", WINDOW_AUTOSIZE);
	imshow("Frame4", img5);

//	Mat imgres(480, 640, CV_8UC1, Scalar(255));
	
	
	
	waitKey(0);
}