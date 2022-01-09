#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;


// ____________________VIRTUAL PAINTER - Project #1________________________

// Logic
// 1. Find colors using HSV colors
// 2. Find contours
// 3. Create a circle at the point (x,y)


int main();

// main image fed from video frames
Mat img;

// newPoints is a vector which holds multiple vectors which hold integers
// { {x-val, y-val, color val}, {}}
std::vector<std::vector<int>> newPoints;


// myColors will hold the HSV thresholds for different colors
std::vector<std::vector<int>> myColors{ {102, 179, 154, 248, 82, 178},  // red
										{72, 179, 141, 255, 43, 237} }; // blue

// shows which color the program draws on the screen
std::vector<Scalar> myColorValues{ {0, 0, 255}, 
								   {255, 0, 0} };


Point getContours(Mat image) {

	std::vector<std::vector<Point>> contours;
	std::vector<Vec4i> hierarchy;
	std::vector<std::vector<Point>> conPoly(contours.size());
	std::vector<Rect> boundRect(contours.size());
	Point myPoint(0, 0);

	findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	

	// filtering noise, adding a filter for area
	for (int i{ 0 }; i < contours.size(); i++) {
		double area = contourArea(contours[i]);
		if (area > 1000) {
			double perimeter = arcLength(contours[i], true);

			approxPolyDP(contours[i], conPoly[i], 0.02 * perimeter, true);
			boundRect[i] = boundingRect(conPoly[i]);

			myPoint.x = boundRect[i].x + (boundRect[i].width / 2);
			myPoint.y = boundRect[i].y;

			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
		}
	}

	return myPoint;
}


std::vector<std::vector<int>> findColor(Mat img) {
	Mat imgHSV;

	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	for (int i{ 0 }; i < myColors.size(); i++) {
		Scalar lower(myColors[i][0], myColors[i][2], myColors[i][4]);
		Scalar upper(myColors[i][1], myColors[i][3], myColors[i][5]);

		Mat mask;
		inRange(imgHSV, lower, upper, mask);
		 // imshow(std::to_string(i), mask);
		Point myPoint = getContours(mask);

		if ((myPoint.x != 0) && (myPoint.y != 0)) {
			newPoints.push_back({ myPoint.x, myPoint.y, i });
		}
	}

	return newPoints;
}


void drawOnCanvas(std::vector<std::vector<int>> newPoints, std::vector<Scalar> myColorValues) {

	for (std::size_t i{ 0 }; i < newPoints.size(); i++) {
		circle(img, Point(newPoints[i][0], newPoints[i][1]), 10, myColorValues[newPoints[i][2]], FILLED);
	}
}




int main() {
	VideoCapture cap(0);

	while (true) {
		cap.read(img);
		newPoints = findColor(img);
		drawOnCanvas(newPoints, myColorValues);

		imshow("Video", img);
		waitKey(1);
	}



	return 0;
}