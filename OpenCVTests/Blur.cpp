#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat blur_test(Mat& src)
{
    Mat dst;
    blur(src, dst, Size(9, 9));
    return dst;
}

Mat gaussian_blur_test(Mat& src)
{
    Mat dst;
    GaussianBlur(src, dst, Size(19, 19), 0, 0);
    return dst;
}