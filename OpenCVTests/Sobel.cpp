#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat sobel_test(Mat& src)
{
	GaussianBlur(src, src, Size(3, 3), 0, 0);
	cvtColor(src, src, CV_BGR2GRAY);

	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	Mat grad;

	Sobel(src, grad_x, CV_16S, 1, 0, 3, 1.0f, 0.0f, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	Sobel(src, grad_y, CV_16S, 0, 1, 3, 1.0f, 0.0f, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5f, 0, grad);

	return grad;
}
