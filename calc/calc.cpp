#include "ChickenVision/HSVThresh.h"
#include "ChickenVision/Smoothing.h"
#include "ChickenVision/Tracking.h"
#include "ChickenVision/VisionProcessing.h"
#include "ChickenVision/Calculation.h"

using namespace cv;

int main()
{
	// create vp object and open the camera at ID 0
	VisionProcessing vp(0);
	vp.visionOpen();

	// set resolution of camera
	vp.setResolution(320, 240);
	while (true)
	{
		// create and get current image from camera
		Mat source;
		source = vp.getFrame();
		// show current image from camera and name window source(src)
		vp.showFrame(source, "src");

		// convert image from RGB colorspace to HSV colorspace
		Mat hsv = RGB2HSV(source);
		vp.showFrame(hsv, "hsv");

		// filter image to exclude parts not between the two scalars
		//Mat hsvFiltered = HSVFilter(hsv); // for sliders
		Mat hsvFiltered = HSVFilter(hsv, Scalar(0, 0, 193), Scalar(84, 255, 255)); // hard coded filter
		vp.showFrame(hsvFiltered, "hsvFiltered");

		// find contour
		vector<vector<Point> > contours = getContours(hsvFiltered);

		// find rectangle surrounding contour with largest area
		Rect bounding_rect = boundRectContour(contours, MAX_AREA);
		Mat area = drawRect(source, bounding_rect, Scalar(50, 200, 10));
		vp.showFrame(area, "area");

		// calculate Distance and angle to target from camera
		double distance = calculateDistance(bounding_rect.height);
		double angle = calculateAngle(distance);
		cout << "Distance: "<<distance<< " Angle: "<< angle<<endl;

		Point_<double> aim = P2ACoor(Point_<double>(bounding_rect.x,bounding_rect.y), Point_<double>(320,240), false);
		cout << "x: "<< aim.x << " y: "<<aim.y<<endl;

		// stop camera when key 'c' is pressed
		// MANDATORY in all programs bc of waitKey
		vp.visionStopWhen('c');
	}
	return 0;
}
