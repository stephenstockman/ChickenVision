# ChickenVision

Very basic collection of functions and classes used in vision processing utilizing OpenCV 3.2 created to be used and modified by FRC Team 217 the ThunderChickens. 

## Features

* Redifined useful OpenCV functions and eliminated extraneous parameters
* Combined common OpenCV code into a class or method 
* Created dynamic GUI control for use in debugging 
* Contains example code in both procedural and object-oriented fashion

## Getting Started

Download folder and place in stored location.

### Prerequisites

* Windows 10
* Eclipse Luna,Mars, or Neon <link> <https://www.eclipse.org/downloads/>
* minGW-w64 <link><https://sourceforge.net/projects/mingw-w64/>
* cMake current version Windows win64-x64 Installer.msi <link> <https://cmake.org/download/>
* OpenCV 3.2.0 <link> <https://sourceforge.net/projects/opencvlibrary/files/opencv-win/3.2.0/opencv-3.2.0-vc14.exe/download>
* ChickenVision Folder and archive folder


### Installing

Video of setup by some guy on YouTube in case you want it <link> <https://www.youtube.com/watch?v=BBamKg5_JKI>
* Run eclipse installer and install Eclipse for C++
* Run minGW-w64 installer and for Architecture select x86_64 "NOT i686"
* Now set the env var for minGW- System->Advanced System Settings->Environment Variables
* Go to System variables and double click PATH->New-> and type C:\Program Files\mingw-w64\x86_64-7.1.0-posix-seh-rt_v5-rev0\mingw64\bin (this should be the directory to your mingw-w64 bin folder so confirm its in the correct location and modify as needed)
* Run OpenCV installer and place somewhere that you can easily find but never plan to move( I reccomend either extract to C:\ or in C:\Users\username\ )
* Run CMake installer and install cMake. Run it.
* Select Browse sources and navigate to the opencv/sources/ folder. Select Browse Build and create a new folder in opencv/ called mybuild.
* Click Configure for the generator select Eclipse CDT4-MinGW Makefiles and wait for it to finish then click generate(note its okay that some tests failed)
* Open Eclipse adn File-> import-> existing project into workspace. For root director selct the mybuild folder you just generated and make sure the box with the project name is checked. Also ensure all of the Options and Working set boxes are unchecked.
* Wait for the c++ indexer to finish(lower right hand corner should take a couple minutes) then left click the project and select Build all, this will take a long time(30 minutes-1 hour).
* Then right click the imported project Build Targets-> Build scroll to the bottom-> :install. This will create the opencv/mybuild/install/ folder and files.

## Deployment
Below I outline how to use it on a windows machine in Eclipse for development purposes and how to use it on the raspberry pi.

### Windows Eclipse

### Raspberry Pi

## Authors

**Stephen Stockman** - ThunderChicken Programmer 2014-2016

## Acknowledgments

Good luck fellow ThunderChicken Programmers may your exposure be set to low and your camera calibration go well
