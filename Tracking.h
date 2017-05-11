/*
 * Tracking.h
 *
 *  Created on: May 5, 2017
 *  Author: Stephen Stockman
 *  ThunderChicken Alumni Invent Libraries (TAIL)
 */
#ifndef TRACKING_H
#define TRACKING_H

#include "opencv2/video/video.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>
#include <iostream>

using namespace std;
using namespace cv;

enum narrowCriteria
{
	//http://docs.opencv.org/3.1.0/d1/d32/tutorial_py_contour_properties.html
	AREA,
	ASPECT_RATIO,
	EXTENT,
	ORIENTATION
};

enum contourCriteria
{
	MAX_AREA, MIN_AREA
};

int minAV=0,maxAV=0;
int minARV=0,maxARV=0;
int minEV=0,maxEV=0;
int minOV=0,maxOV=0;
vector<vector<Point> > getContours(Mat &frame)
{
	// contour detection
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Mat drawing = Mat::zeros(frame.size(), CV_8UC3);

	findContours(frame, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE,
			Point(0, 0));
	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(217, 217, 217);
		drawContours(drawing, contours, (int) i, color, 2, 8, hierarchy, 0,
				Point());
	}
	namedWindow("Contours", WINDOW_AUTOSIZE);
	imshow("Contours", drawing);

	return contours;
}

vector<vector<Point>> narrowContours(vector<vector<Point> > contoursIn,
		narrowCriteria crit, Point_<double> range)
{
	vector<vector<Point>> contoursOut;
	//Point(min,max)
	double min = range.x;
	double max = range.y;

	switch (crit)
	{
	case AREA: // find contours with an area between min and max
	{
		for (int i = 0; i < contoursIn.size(); i++) // iterate through each contour.
		{
			double a = contourArea(contoursIn[i], false); //  Find the area of contour
			if (a >= min && a <= max)
			{
				contoursOut.push_back(contoursIn[i]);
			}
		}
	}
		break;

		// AR=width/height; so Point(min,max) should be Point(AR of real life object-error,AR of real life object+error)
		// error is determined by how much AR changes when viewing he target from different side angles
	case ASPECT_RATIO: // find contours with an aspect ratio between min and max
	{
		for (int i = 0; i < contoursIn.size(); i++) // iterate through each contour.
		{
			Rect bounding_rect = boundingRect(contoursIn[i]); // Find the bounding rectangle for biggest contour
			double ar = ((double) bounding_rect.width)
					/ ((double) bounding_rect.height);

			if (ar >= min && ar <= max)
			{
				contoursOut.push_back(contoursIn[i]);
			}
		}
	}
		break;
		//EX=(contour area)/ (bounding rect area); so basically ratio of the contour or what you are tracking
		// divided by the area of the rectangle that surrounds it
	case EXTENT:
	{
		min = ((double) min) / 10.0;
		max = ((double) max) / 10.0;
		for (int i = 0; i < contoursIn.size(); i++) // iterate through each contour.
		{
			Rect bounding_rect = boundingRect(contoursIn[i]); // Find the bounding rectangle for biggest contour
			double ex = contourArea(contoursIn[i], false)
					/ (bounding_rect.width * bounding_rect.height);
			if (ex >= min && ex <= max)
			{
				contoursOut.push_back(contoursIn[i]);
			}
		}
	}
		break;

		// checks the angle by making a rectangl that rotates with the tracked object
		// buggy- fitEllipse can flicker between 0,90,180 at same position
		// suspected bug- method used in getContours aka RETR_EXTERNAL or CHAIN_APPROX_SIMPLE
	case ORIENTATION:
	{
		for (int i = 0; i < contoursIn.size(); i++) // iterate through each contour.
		{
			Mat pointsf;
			Mat(contoursIn[i]).convertTo(pointsf, CV_32F);
			if (contoursIn[i].size() > 5)
			{
				RotatedRect box = fitEllipse(pointsf);

				double angle = box.angle;
				while(angle > max)
				{
					angle = angle-90;
				}
				if ((angle >= min && angle <= max) )
				{
					contoursOut.push_back(contoursIn[i]);
				}
			}
		}
	}
		break;
	}
	return contoursOut;
}

void sliderNarrowInit(narrowCriteria crit)
{
	namedWindow("Sliders Narrow", 1);
	String name;
	int cap;
	switch(crit)
	{
	case AREA:
	{
		name="Area";
		cap = 320*240/4;//cap should be less than max resolution 1/4 is decent
		// Create Trackbars
			createTrackbar(name+" Min", "Sliders Narrow", &minAV, cap);
			createTrackbar(name+" Max", "Sliders Narrow", &maxAV, cap);
	}break;
	case ASPECT_RATIO:
	{
		name="AspectRatio";
		cap = 5;
		// Create Trackbars
			createTrackbar(name+" Min", "Sliders Narrow", &minARV, cap);
			createTrackbar(name+" Max", "Sliders Narrow", &maxARV, cap);
	}break;
	case EXTENT:
	{
		name="Extent";
		cap = 1;// cap is 100% ie area of object fills entirety of bounded
		// Create Trackbars
			createTrackbar(name+" Min", "Sliders Narrow", &minEV, cap);
			createTrackbar(name+" Max", "Sliders Narrow", &maxEV, cap);
	}break;
	case ORIENTATION:
	{
		name = "Orientation";
		cap = 20;// cap is 20 degrees.. eh kinda arbitrary
		// Create Trackbars
	    createTrackbar(name+"+-", "Sliders Narrow", &minOV, cap);
	}break;
	}

}

vector<vector<Point>> narrowContours(vector<vector<Point> > contoursIn,narrowCriteria crit)
{
	sliderNarrowInit(crit);
	vector<vector<Point>> contoursOut;

	switch (crit)
	{
	case AREA: // find contours with an area between min and max
	{
		for (int i = 0; i < contoursIn.size(); i++) // iterate through each contour.
		{
			double a = contourArea(contoursIn[i], false); //  Find the area of contour
			if (a >= minAV && a <= maxAV)
			{
				contoursOut.push_back(contoursIn[i]);
			}
		}
	}
		break;

		// AR=width/height; so Point(min,max) should be Point(AR of real life object-error,AR of real life object+error)
		// error is determined by how much AR changes when viewing he target from different side angles
	case ASPECT_RATIO: // find contours with an aspect ratio between min and max
	{
		for (int i = 0; i < contoursIn.size(); i++) // iterate through each contour.
		{
			Rect bounding_rect = boundingRect(contoursIn[i]); // Find the bounding rectangle for biggest contour
			double ar = ((double) bounding_rect.width)
					/ ((double) bounding_rect.height);
			if (ar >= minARV && ar <= maxARV)
			{
				contoursOut.push_back(contoursIn[i]);
			}
		}
	}
		break;
		//EX=(contour area)/ (bounding rect area); so basically ratio of the contour or what you are tracking
		// divided by the area of the rectangle that surrounds it
	case EXTENT:// useless please dont use
	{
		for (int i = 0; i < contoursIn.size(); i++) // iterate through each contour.
		{
			Rect bounding_rect = boundingRect(contoursIn[i]); // Find the bounding rectangle for biggest contour
			double ex = contourArea(contoursIn[i], false)
					/ (bounding_rect.width * bounding_rect.height);
			if (ex >= minEV && ex <= maxEV)
			{
				contoursOut.push_back(contoursIn[i]);
			}
		}
	}
		break;

		// checks the angle by making a rectangl that rotates with the tracked object
		// buggy- fitEllipse can flicker between 0,90,180 at same position
		// suspected bug- method used in getContours aka RETR_EXTERNAL or CHAIN_APPROX_SIMPLE
	case ORIENTATION:
	{
		for (int i = 0; i < contoursIn.size(); i++) // iterate through each contour.
		{
			Mat pointsf;
			Mat(contoursIn[i]).convertTo(pointsf, CV_32F);
			if (contoursIn[i].size() > 5)
			{
				RotatedRect box = fitEllipse(pointsf);

				double angle = box.angle;
				while(angle > minOV)
				{
					angle = angle-90;
				}
				if ((angle >= -minOV && angle <= minOV) )
				{
					contoursOut.push_back(contoursIn[i]);
				}
			}
		}
	}
		break;
	}
	return contoursOut;
}

Rect boundRectContour(vector<vector<Point> > contours, contourCriteria crit)
{
	Rect bounding_rect;
	switch (crit)
	{
	case MAX_AREA: // find contour with greatest area
	{
		double max = 0;
		for (int i = 0; i < contours.size(); i++) // iterate through each contour.
		{
			double a = contourArea(contours[i], false); //  Find the area of contour

			if (a > max)
			{
				max = a;
				bounding_rect = boundingRect(contours[i]); // Find the bounding rectangle for biggest contour
			}
		}
	}
		break;

	case MIN_AREA: //find contour with lowest area
	{
		double min = 0;
		for (int i = 0; i < contours.size(); i++) // iterate through each contour.
		{
			double a = contourArea(contours[i], false); //  Find the area of contour

			if (a < min)
			{
				min = a;
				bounding_rect = boundingRect(contours[i]); // Find the bounding rectangle for biggest contour
			}
		}
	}
		break;
	}
	return bounding_rect;
}

Mat drawRect(Mat src, Rect bounding_rect, Scalar color)
{
	rectangle(src, bounding_rect, color, 2, 8, 0);
	String coor = "x: " + to_string(bounding_rect.x) + " y: "
			+ to_string(bounding_rect.y);
	putText(src, coor, Point(20, 20), FONT_HERSHEY_COMPLEX_SMALL, 1,
			color, 2, 8);
	return src;
}

#endif
