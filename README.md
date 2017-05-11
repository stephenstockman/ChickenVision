#ChickenVision Examples
Included in this branch are a series of example projects demonstrating ChickenVision.

##Project Descriptions

* proceduralTrackerExample- an example that uses ChickenVision to demonstrate how one would go about making a tracking program to track retroreflective tape. You can run it but note that the hardcoded vaues won't work as they were determined by tracking a random object-ie my phone with a green background. As such comment out the HSVFilter and both the narrowContours and uncomment the "for sliders" lines.

* classTrackerExample- same as proceduralTrackerEcample but does so in an object-oriented manner.

* fullDebugExample- shows off a bunch of different sliders giving the user full control to tune their vision. Something like this could be useful during the camera calibration period at competitions or during build season. It is also meant as an educational tool to help new programmers understand how vision filters through contours.

* calcExample- demonstrates calculating distance to objects and finding the angle to said object using a phone as a tracked object.Really only useful for code absolutely useless to run as the objects you plan to track will change the values in the code dramatically. If you want to use this code you must change all the values at the top of Calculation.h to the correct values.
