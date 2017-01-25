#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

#define BLEND_ALPHA 0.1f
static Mat* bg = nullptr;

Mat additive_background_test(Mat& src)
{
	if (bg == nullptr)
	{
		bg = new Mat();
		*bg = src.clone();
	}

	addWeighted(src, BLEND_ALPHA, *bg, 1.0 - BLEND_ALPHA, 0.0, *bg);

	return *bg;
}

Mat motion_detection_test(Mat& src)
{
	if (bg == nullptr)
	{
		bg = new Mat();
		*bg = src.clone();
	}

	addWeighted(src, BLEND_ALPHA, *bg, 1.0 - BLEND_ALPHA, 0.0, *bg);

	unsigned int intensity = 0;
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			intensity = abs(src.data[i*src.step[0] + j * 3 + 0] - bg->data[i*src.step[0] + j * 3 + 0]);
			intensity += abs(src.data[i*src.step[0] + j * 3 + 1] - bg->data[i*src.step[0] + j * 3 + 1]);
			intensity += abs(src.data[i*src.step[0] + j * 3 + 2] - bg->data[i*src.step[0] + j * 3 + 2]);
			if (intensity > 80)
			{
				src.data[i*src.step[0] + j * 3 + 0] = 255;
				src.data[i*src.step[0] + j * 3 + 1] = 255;
				src.data[i*src.step[0] + j * 3 + 2] = 255;
			}
		}
	}

	return src;
}