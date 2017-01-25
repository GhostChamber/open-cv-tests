#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

cv::Mat additive_background_test(cv::Mat& src);

cv::Mat motion_detection_test(cv::Mat& src);