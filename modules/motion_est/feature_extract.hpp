#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
namespace vsl
{
    void find_feature_matches(cv::Mat const &img_1, cv::Mat const &img_2,
                              std::vector<cv::KeyPoint> &keypoints_1,
                              std::vector<cv::KeyPoint> &keypoints_2,
                              std::vector<cv::DMatch> &matches);
}