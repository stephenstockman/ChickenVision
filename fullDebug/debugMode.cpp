#include "ChickenVision/HSVThresh.h"
#include "ChickenVision/Smoothing.h"
#include "ChickenVision/Tracking.h"
#include "ChickenVision/VisionProcessing.h"

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


		// blur image
		Mat smooth = smoothAverage(hsv);
		smooth = smoothGuassian(hsv);
		smooth = smoothMedian(hsv);
		smooth = dilation(hsv);
		smooth = erosion(hsv);
		smooth = smoothBilateral(hsv);//must be last blur if combined with other blurs bc of bug
		vp.showFrame(smooth, "smooth");

		// filter image to exclude parts not between the two scalars
		Mat hsvFiltered = HSVFilter(smooth); // for sliders
		//Mat hsvFiltered = HSVFilter(smooth, Scalar(29, 0, 60), Scalar(75, 255, 255)); // hard coded filter
		vp.showFrame(hsvFiltered, "hsvFiltered");

		// find contour
		vector<vector<Point> > contours = getContours(hsvFiltered);

		// narrow contours
		contours = narrowContours(contours, AREA,Point(1000,40000));
		contours = narrowContours(contours, ASPECT_RATIO);
		//contours = narrowContours(contours, EXTENT,Point(0,8));
		contours = narrowContours(contours, ORIENTATION);

		// find rectangle surrounding contour with largest area
		Rect bounding_rect = boundRectContour(contours, MAX_AREA);
		Mat area = drawRect(source, bounding_rect, Scalar(50, 200, 10));
		vp.showFrame(area, "area");

		// stop camera when key 'c' is pressed
		// MANDATORY in all programs bc of waitKey
		vp.visionStopWhen('c');
	}
	return 0;
}
