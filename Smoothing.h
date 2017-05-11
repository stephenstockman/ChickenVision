/*
 * Smoothing.h
 *
 *  Created on: May 5, 2017
 *  Author: Stephen Stockman
 *  ThunderChicken Alumni Invent Libraries (TAIL)
 */
#ifndef SMOOTHING_H
#define SMOOTHING_H
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;

int ksizeAverage = 0, ksizeGuassian = 0, ksizeMedian = 0, ksizeBilateral = 0;
int ksizeDilation = 0, ksizeErosion = 0;

void sliderAverageInit()
{
	namedWindow("Sliders", 1);

	// Create Trackbars
	createTrackbar("Average", "Sliders", &ksizeAverage, 20);
}

Mat smoothAverage(Mat frame)
{
	sliderAverageInit();
	Mat smooth = frame;
	// same as boxFilter
	if (ksizeAverage > 0)
	{
		blur(frame, smooth, Size(ksizeAverage, ksizeAverage));
	}
	return smooth;
}

// Blur an image using normalized box filter of side length ksize
// use to just blur an image
Mat smoothAverage(Mat frame, int ksize)
{
	Mat smooth;
	// same as boxFilter
	blur(frame, smooth, Size(ksize, ksize));
	return smooth;
}

void sliderGuassianInit()
{
	namedWindow("Sliders", 1);

	// Create Trackbars
	createTrackbar("Guassian", "Sliders", &ksizeGuassian, 40);
}

Mat smoothGuassian(Mat frame)
{
	sliderGuassianInit();
	Mat smooth = frame;

	if (ksizeGuassian > 0 && ksizeGuassian % 2 == 1)
	{
		GaussianBlur(frame, smooth, Size(ksizeGuassian, ksizeGuassian), 0, 0);
	}
	else if (ksizeGuassian > 0 && ksizeGuassian % 2 == 0)
	{
		GaussianBlur(frame, smooth, Size(ksizeGuassian - 1, ksizeGuassian - 1),
				0, 0);
	}
	return smooth;
}

// remove guassian noise(random pixels)
// use to remove small blemishes near object or to merge like colored objects
Mat smoothGuassian(Mat frame, int ksize)
{
	Mat smooth;
	GaussianBlur(frame, smooth, Size(ksize, ksize), 0, 0);
	return smooth;
}

void sliderMedianInit()
{
	namedWindow("Sliders", 1);

	// Create Trackbars
	createTrackbar("Median", "Sliders", &ksizeMedian, 20);
}

Mat smoothMedian(Mat frame)
{
	sliderMedianInit();
	Mat smooth = frame;

	if (ksizeMedian > 0 && ksizeMedian % 2 == 1)
	{
		medianBlur(frame, smooth, ksizeMedian);
	}
	else if (ksizeMedian > 0 && ksizeMedian % 2 == 0)
	{
		medianBlur(frame, smooth, ksizeMedian - 1);
	}
	return smooth;
}

// find median of box with side length ksize and set that to center of box
// use to remove salt and pepper noise( old TV static[can be any color])
Mat smoothMedian(Mat frame, int ksize)
{
	Mat smooth;
	medianBlur(frame, smooth, ksize);
	return smooth;
}

void sliderBilateralInit()
{
	namedWindow("Sliders", 1);

	// Create Trackbars
	createTrackbar("Bilateral", "Sliders", &ksizeBilateral, 40);
}

Mat smoothBilateral(Mat frame)
{
	sliderBilateralInit();
	Mat smooth;//bug can't combine with dilation bc no = frame

	if (ksizeBilateral > 0)
	{
		bilateralFilter(frame, smooth, ksizeBilateral, ksizeBilateral * 2,
				ksizeBilateral / 2);
	}
	else if (ksizeBilateral == 0)
	{
		return frame;
	}
	return smooth;
}
// does a guassian blur but only considers nearby pixels that have a similar intensity
// use to blur an image but preserve distinct edges between different objects
Mat smoothBilateral(Mat frame, int ksize)
{
	Mat smooth;
	bilateralFilter(frame, smooth, ksize, ksize * 2, ksize / 2);
	return smooth;
}

void sliderDilationInit()
{
	namedWindow("Sliders", 1);

	// Create Trackbars
	createTrackbar("Dilation", "Sliders", &ksizeDilation, 20);
}

Mat dilation(Mat frame)
{
	sliderDilationInit();
	Mat dil=frame;

	if (ksizeDilation > 0)
	{
		Mat element = getStructuringElement(MORPH_RECT,
				Size(2 * ksizeDilation + 1, 2 * ksizeDilation + 1),
				Point(ksizeDilation, ksizeDilation));
		dilate(frame, dil, element);
	}
	return dil;
}


// enlarge pronounced objects
Mat dilation(Mat frame, int ksize)
{
	Mat dil;
	Mat element = getStructuringElement(MORPH_RECT,
			Size(2 * ksize + 1, 2 * ksize + 1), Point(ksize, ksize));
	dilate(frame, dil, element);
	return dil;
}

void sliderErosionInit()
{
	namedWindow("Sliders", 1);

	// Create Trackbars
	createTrackbar("Erosion", "Sliders", &ksizeErosion, 20);
}

Mat erosion(Mat frame)
{
	sliderErosionInit();
	Mat dil=frame;

	if (ksizeErosion > 0)
	{
		Mat element = getStructuringElement(MORPH_RECT,
				Size(2 * ksizeErosion + 1, 2 * ksizeErosion + 1), Point(ksizeErosion, ksizeErosion));
		erode(frame, dil, element);
	}
	return dil;
}
// shrink pronounced objects
Mat erosion(Mat frame, int ksize)
{
	Mat dil;
	Mat element = getStructuringElement(MORPH_RECT,
			Size(2 * ksize + 1, 2 * ksize + 1), Point(ksize, ksize));
	erode(frame, dil, element);
	return dil;
}
#endif
