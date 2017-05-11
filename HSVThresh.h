/*
 * HSVThresh.h
 *
 *  Created on: May 5, 2017
 *  Author: Stephen Stockman
 *  ThunderChicken Alumni Invent Libraries (TAIL)
 */
#ifndef HSVTHRESH_H
#define HSVTHRESH_H

#include "opencv2/video/video.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

int hueMin = 0, satMin = 0, valMin = 0; // min values for HSV range
int hueMax = 180, satMax = 255, valMax = 255; // max values for HSV range


// call to create the sliders before HSVFilter
void sliderHSVInit()
{
	namedWindow("Sliders",1);

	// Create Trackbars
	createTrackbar("Hue Min", "Sliders", &hueMin, 180);
	createTrackbar("Sat Min", "Sliders", &satMin, 255);
	createTrackbar("Val Min", "Sliders", &valMin, 255);
	createTrackbar("Hue Max", "Sliders", &hueMax, 180);
	createTrackbar("Sat Max", "Sliders", &satMax, 255);
	createTrackbar("Val Max", "Sliders", &valMax, 255);

}

// convert image from rgb colorspace to hsv colorspace
Mat RGB2HSV(Mat rgb)
{
	Mat hsv;
	cvtColor(rgb, hsv, CV_RGB2HSV);
	return hsv;
}

// hsv filter based on range from sliders
Mat HSVFilter(Mat hsv){
	sliderHSVInit();
	Mat hsvFiltered;
	inRange(hsv, Scalar(hueMin, satMin, valMin), Scalar(hueMax,satMax,valMax), hsvFiltered);
	return hsvFiltered;
}

// hsv filter from ranges manually provided
// example Scalar(50,20,30) or Scalar(hue,sat,val) could be passed in
// also Scalar scal = (50,20,30); then pass in scal to HSVFilter
Mat HSVFilter(Mat frame,Scalar min, Scalar max)
{
	Mat hsvFiltered;
	inRange(frame, min, max, hsvFiltered);
	return hsvFiltered;
}

#endif

