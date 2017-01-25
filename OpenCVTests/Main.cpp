#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Blur.h"
#include "Sobel.h"
#include "BackgroundSubtraction.h"

using namespace cv;
using namespace std;

enum TestEnum
{
	TEST_BLUR = 0,
	TEST_GAUSSIAN_BLUR = 1,
	TEST_SOBEL = 2,
	TEST_ADDITIVE_BACKGROUND = 3,
	TEST_MOTION_DETECTION = 4,

	NUM_TESTS = 5
};

int main(int argc, char** argv)
{

    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cout << "Cannot open the video camera.\n";
        return -1;
    }

    double width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    double height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    cout << "Frame size: " << width << " x " << height << "\n";

    namedWindow("Ghost Stream", CV_WINDOW_FREERATIO);

    Mat cam;

	unsigned int currentTest = TEST_BLUR;
	bool prevKeyDown  = false;

    while (true)
    {
		bool success = cap.read(cam);
		Mat render;

		// Handle left/right input for changing test operation.
		if (GetAsyncKeyState(VK_LEFT) &&
			!prevKeyDown)
		{
			currentTest--;
			prevKeyDown = true;
		}
		else if (GetAsyncKeyState(VK_RIGHT) &&
			!prevKeyDown)
		{
			currentTest++;
			prevKeyDown = true;
		}
		else if (GetAsyncKeyState(VK_RIGHT) ||
			GetAsyncKeyState(VK_LEFT))
		{
			prevKeyDown = true;
		}
		else
		{
			prevKeyDown = false;
		}


		if (currentTest < 0)
		{
			currentTest = 0;
		}
		else if (currentTest >= NUM_TESTS)
		{
			currentTest = NUM_TESTS - 1;
		}

		switch (currentTest)
		{
		case TEST_BLUR:
			render = blur_test(cam);
			break;
		case TEST_GAUSSIAN_BLUR:
			render = gaussian_blur_test(cam);
			break;
		case TEST_SOBEL:
			render = sobel_test(cam);
			break;
		case TEST_ADDITIVE_BACKGROUND:
			render = additive_background_test(cam);
			break;
		case TEST_MOTION_DETECTION:
			render = motion_detection_test(cam);
			break;
		default:
			break;
		}

		if (!success)
		{
			std::cout << "Cannot read a frame from video stream" << "\n";
		}
		else
		{
			imshow("Ghost Stream", render);
		}

		if (waitKey(30) == 27)
		{
			std::cout << "Exiting application based on user input.\n";
			break;
		}
	}
}
