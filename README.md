# ChickenVision Examples

Included in this branch are a series of example projects demonstrating ChickenVision.

## Project Descriptions
 * proceduralTrackerExample- an example that uses ChickenVision to demonstrate how one would go about making a tracking program to track retroreflective tape. In this program we use the gui sliders to find the values for the hsvfilter and then narrow down the search o only track objects that fall netween a minimum and maximum area. Modifications- comment the hsvfilter slider line and uncomment the hard coded version and add in the number you found by running it with the sliders. Modify the area boundings to include a wider or smaller range of areas and add in additional narrowContours to further refine and confirm the tracked objects identity.
 
 * classTrackerExample- same as proceduralTrackerEcample but does so in ano object-oriented manner. However this project also shows the difference that having one narrowContour and having two can make in object detection.
 
 * fullDebugExample- shows off a bunch of different sliders giving the user full control to tune their vision. Something like this could be useful during the cameraCalibration period at competitions or during build season. It is also menat as an educational tool to help new programmers understand how vision filters through contours.
 
* calcExample- demonstrates calculating distance to objects and finding the angle to said object using a phone as a tracked object.Really only useful for code absolutely useless to run as the objects you plan to track will change the values in the code dramatically.

