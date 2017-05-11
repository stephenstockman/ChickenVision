/*
 * proceduralExample.cpp
 *
 *  Created on: May 5, 2017
 *  Author: Stephen Stockman
 *  ThunderChicken Alumni Invent Libraries (TAIL)
 */
#include "HSVThresh.h"
#include "Smoothing.h"
#include "Tracking.h"
#include "VisionProcessing.h"

using namespace cv;
using namespace std;

int main()
{
	// create vp object and open the camera at ID 0
	VisionProcessing vp(0);
	vp.visionOpen();

	// set resolution of camera
	vp.setResolution(320, 240);

	while (true) //TODO: make a more FMS friendly loop
	{
		// create and get current image from camera
		Mat source;
		source = vp.getFrame();
		// show current image from camera and name window source(src)
		vp.showFrame(source, "src");

		// convert image from RGB colorspace to HSV colorspace
		Mat hsv = RGB2HSV(source);
		vp.showFrame(hsv,"hsv");

		// blur image
		Mat smooth = smoothAverage(hsv, 5);
		vp.showFrame(smooth,"smooth");

		// filter image to exclude parts not between the two scalars
		Mat hsvFiltered = HSVFilter(smooth); // for sliders
		//Mat hsvFiltered = HSVFilter(smooth, Scalar(29, 0, 60), Scalar(75, 255, 255)); // hard coded filter
		vp.showFrame(hsvFiltered, "hsvFiltered");

		// find contour
		vector<vector<Point> > contours = getContours(hsvFiltered);

		// narrow contours
		contours = narrowContours(contours, AREA, Point(2000,10000));
		//contours = narrowContours(contours, ASPECT_RATIO, Point(1,2));
		//contours = narrowContours(contours, EXTENT, Point(0,4));// really 0.0 and 0.4
		//contours = narrowContours(contours, ORIENTATION, Point(-15,15));// kinda buggy


		// find rectangle surrounding contour with largest area
		Rect bounding_rect = boundRectContour(contours,MAX_AREA);
		Mat area = drawRect(source, bounding_rect,Scalar(50,200,10));
		vp.showFrame(area,"area");

		// find rectangle satisfying area and AR restraints
		source = vp.getFrame();
		contours = narrowContours(contours, ASPECT_RATIO, Point(1,2));
		Rect boundingCRect = boundRectContour(contours,MAX_AREA);
		Mat areaAR = drawRect(source, boundingCRect,Scalar(150,10,10));
		vp.showFrame(areaAR,"areaAR");

		// stop camera when key 'c' is pressed
		// MANDATORY in all programs bc of waitKey
		vp.visionStopWhen('c');
	}
	return 0;

}
