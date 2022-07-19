#pragma once

#include <opencv2/opencv.hpp>
#include <vector>


namespace zLimbo {

	void myConvexHull(std::vector<cv::Point2f> &points, std::vector<int> &hull);
	void myConvexHull2(std::vector<cv::Point2f> &points, std::vector<int> &hull);
}

