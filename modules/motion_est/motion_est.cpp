#include <math.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <Eigen/Dense>
#include "calibration.hpp"
#include "eigen_utils.hpp"
#include "motion_est.hpp"
#include <vector>
#include <opencv2/calib3d.hpp>
#include <opencv2/features2d.hpp>
#include "feature_extract.hpp"
#include "utils.hpp"

namespace vsl
{
    std::tuple<Eigen::Matrix3d, Eigen::Vector3d> estimate_motion(cv::Mat const &img1, cv::Mat const &img2, Eigen::Vector4d camera_intrinsics)
    {
        std::vector<cv::KeyPoint> keypts1;
        std::vector<cv::KeyPoint> keypts2;
        std::vector<cv::DMatch> matches;
        find_feature_matches(img1, img2, keypts1, keypts2, matches);

        std::vector<cv::Point2f> points1;
        std::vector<cv::Point2f> points2;
        for (int i = 0; i < (int)matches.size(); i++)
        {
            points1.push_back(keypts1[matches[i].queryIdx].pt);
            points2.push_back(keypts2[matches[i].trainIdx].pt);
        }

        // 计算相机矩阵
        double fx = camera_intrinsics(0),
               fy = camera_intrinsics(1),
               cx = camera_intrinsics(2),
               cy = camera_intrinsics(3);

        // 相机矩阵
        cv::Mat_<double> K(3, 3);
        K << fx, 0, cx,
            0, fy, cy,
            0, 0, 1;

        // 关键矩阵
        cv::Mat E = cv::findEssentialMat(points1, points2, K);
        cv::Mat R, t;
        cv::recoverPose(E, points1, points2, K, R, t);
        Eigen::Matrix3d eig_R;
        eig_R << R.at<double>(0, 0), R.at<double>(0, 1), R.at<double>(0, 2),
            R.at<double>(1, 0), R.at<double>(1, 1), R.at<double>(1, 2),
            R.at<double>(2, 0), R.at<double>(2, 1), R.at<double>(2, 2);
        Eigen::Vector3d eig_t(t.at<double>(0), t.at<double>(1), t.at<double>(2));

        return {eig_R, eig_t};
    }
}