/*
 * Tracking.h
 *
 *  Created on: May 5, 2017
 *  Author: Stephen Stockman
 *  ThunderChicken Alumni Invent Libraries (TAIL)
 */
#ifndef CHICKENVISION_CALCULATION_H_
#define CHICKENVISION_CALCULATION_H_
#include <math.h>;

using namespace cv;

// YOU MUST CHANGE THESE CONSTANTS
double FOCAL = 309;// Focal = (measurementPixels*distance2ObjectParallel2Ground)/(measurementObject)
double HEIGHT_OBJECT = 6;// irl measurement
double CAMERA_HEIGHT = 26;// irl measurment
double TARGET_HEIGHT = 48; // irl measurement
#define PI 3.14159265

double calculateDistance(double heightPixels)
{
	// Focal = (measurementPixels*distance2ObjectParallel2Ground)/(measurementObject)
	// distance2ObjectParallel2Ground = (measurementObject*Focal)/(measurementPixels)
	// Example: IPhone 6s screen width=10.2cm, height=6cm; phone in landscape mode ie [     ]
	// From 30cm from camera width in pixels of 105; thus Focal = (105*30)/(10.2) = 309
	// therefore distance to object = (309(focal) * 10.2(width of phone))/(width in pixels from bounded_rect)
	double distance = (FOCAL*HEIGHT_OBJECT)/heightPixels;
	return distance;
}

double calculateAngle(double distance)
{
	// basic trig
	double angle = atan((TARGET_HEIGHT-CAMERA_HEIGHT)/(distance))*180/PI;
	return angle;
}

// pixel Coordinates to Aiming coordinates
Point_<double> P2ACoor(Point_<double> pixel, Point_<double> resolution, bool invert)
{

	double xA = (pixel.x - resolution.x/2)/(resolution.x/2);
	double yA = (pixel.y - resolution.y/2)/(resolution.y/2);
	if(invert)
	{
		xA = -xA;
		yA = -yA;
	}
	return Point_<double>(xA,yA);
}
#endif
