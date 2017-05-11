#include "Tracking.h"
#include "Smoothing.h"
#include "VisionProcessing.h"
#include "HSVThresh.h"

using namespace cv;

class ObjectTracker
{
public:
	Point_<Scalar> hsvRange;
	narrowCriteria nCrit;
	Point nCritRange;
	contourCriteria cCrit;

	// now obviously this is an awful object to make so dont use code like this
	// limit the amount of parameters you need to create te object
	// and make the rest variables that ou can access via member functions
	// TODO: do this ^^ lol
	ObjectTracker(Point_<Scalar> hsvIn, narrowCriteria nCritIn,Point_<int> nCritRangeIn, contourCriteria cCritIn) :
			hsvRange(hsvIn), nCrit(nCritIn), nCritRange(nCritRangeIn), cCrit(cCritIn){}

	Rect findObjectRect(Mat source)
	{
		// filter image to exclude parts not between the two scalars
		Mat hsvFiltered = HSVFilter(source, hsvRange.x, hsvRange.y);

		// find contour
		vector<vector<Point> > contours = getContours(hsvFiltered);

		// narrow contours
		contours = narrowContours(contours, nCrit, nCritRange);

		// find rectangle surrounding contour with largest area
		Rect bounding_rect = boundRectContour(contours, cCrit);

		return bounding_rect;
	}

	vector<vector<Point> > findObjectContours(Mat source)
	{
		// filter image to exclude parts not between the two scalars
		Mat hsvFiltered = HSVFilter(source, hsvRange.x, hsvRange.y);

		// find contour
		vector<vector<Point> > contours = getContours(hsvFiltered);

		// narrow contours
		contours = narrowContours(contours, nCrit, nCritRange);

		return contours;
	}

};

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

		// convert image from RGB colorspace to HSV colorspace
		Mat hsv = RGB2HSV(source);

		// track object to get rect
		ObjectTracker objT(Point_<Scalar>(Scalar(29, 0, 60), Scalar(75, 255, 255)), AREA,Point(2000, 15000), MAX_AREA);
		Rect boundedRect = objT.findObjectRect(hsv);
		Mat area = drawRect(source, boundedRect, Scalar(57, 255, 20));
		vp.showFrame(area, "area");

		// track object to get contours then narrow even more
		source = vp.getFrame();
		vector<vector<Point> > contours = objT.findObjectContours(hsv);
		contours = narrowContours(contours, ASPECT_RATIO, Point(1, 2));
		Rect boundedCRect = boundRectContour(contours, MAX_AREA);
		Mat areaAR = drawRect(source, boundedCRect, Scalar(200, 50, 50));
		vp.showFrame(areaAR, "areaAR");

		// stop camera when key 'c' is pressed
		// MANDATORY in all programs bc of waitKey
		vp.visionStopWhen('c');
	}
	return 0;
}
