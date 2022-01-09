#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;

// _______________________COLOR DETECTION___________________________
// hue min is 180 and saturation and value mins are 255

Mat imgHSV, mask;
int hmin = 0, smin = 110, vmin = 153;
int hmax = 19, smax = 240, vmax = 255;


int main() {
	// std::string path = "Resources/lambo.png";
	// Mat img = imread(path);

	VideoCapture cap{ 0 };
	Mat img;

	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Saturation Min", "Trackbars", &smin, 255);
	createTrackbar("Saturation Max", "Trackbars", &smax, 255);
	createTrackbar("Value Min", "Trackbars", &vmin, 255);
	createTrackbar("Value Max", "Trackbars", &vmax, 255);

	while (true) {
		cap.read(img);

		cvtColor(img, imgHSV, COLOR_BGR2HSV);

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);

		imshow("Image", img);
		imshow("ImageHSV", imgHSV);
		imshow("Mask", mask);
		waitKey(1);
	}
	

	

	return 0;
}