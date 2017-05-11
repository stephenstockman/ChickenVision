/*
 * VisionProcessing.h
 *
 *  Created on: May 5, 2017
 *  Author: Stephen Stockman
 *  ThunderChicken Alumni Invent Libraries (TAIL)
 */
#ifndef VISIONPROCESSING_H
#define VISIONPROCESSING_H

#include "opencv2/video/video.hpp"
#include <stdlib.h>
#include <iostream>

using namespace std;
using namespace cv;

class VisionProcessing
{
public:
	int cameraID; // ID for usb camera-found via web dashboard, default is 0
	VideoCapture vc;

	// default VP constructor
	VisionProcessing() :
			cameraID(0){}

	// VP constructor pass in camera ID
	VisionProcessing(int camID) :
			cameraID(camID){}

	// TODO: constructor that sets values from file


	// ALL THESE PROPRTIES MAY OR MAY NOT WORK DEPENDING ON THE CAMERA
	// ALSO RANGES OF VALUES USED WILL VARY
	// TODO: write  test script to run through values for each setting and report what settings work

	// set width and height of the frames in the video stream
	void setResolution(int width, int height)
	{
		vc.set(CAP_PROP_FRAME_WIDTH, width);
		vc.set(CAP_PROP_FRAME_HEIGHT, height);
	}

	// cap the frame rate of the video stream
	void setFPS(int fps)
	{
		vc.set(CAP_PROP_FPS, fps);
	}

	// brightness of the video stream
	void setBrightness(double bright)
	{
		vc.set(CAP_PROP_BRIGHTNESS, bright);
	}

	// contrast of the video stream
	void setContrast(double contr)
	{
		vc.set(CAP_PROP_CONTRAST, contr);
	}

	// saturation of the video stream
	void setSaturation(double satur)
	{
		vc.set(CAP_PROP_SATURATION, satur);
	}

	// hue of the video stream
	void setHue(double hue)
	{
		vc.set(CAP_PROP_HUE, hue);
	}

	// gain of video stream
	void setGain(double gain)
	{
		vc.set(CAP_PROP_GAIN, gain);
	}

	// exposure of video stream
	void setExposure(double exp)
	{
		vc.set(CAP_PROP_EXPOSURE, exp);
	}

	// open up the camera
	void visionOpen()
	{
		vc.open(cameraID); // open camera
		if (!vc.isOpened() || cameraID < 0)  // check if successful
		{
			cout << "Camera failed to open" << endl;
			exit(EXIT_FAILURE);
		}
	}

	Mat getFrame()
	{
		Mat frame;
		vc >> frame;
		return frame;
	}

	void showFrame(Mat &frame, String name)
	{
		imshow(name, frame);
	}

	void visionStopWhen(char key)
	{
		// stops program by pressing key('c','a','2',etc)
		char keyPress = waitKey(5);
		if (keyPress == key)
		{
			vc.release();
			exit(0);
		}
	}

};
#endif
