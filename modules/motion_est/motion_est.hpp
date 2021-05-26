#pragma once
#include <Eigen/Dense>
#include "calibration.hpp"
#include <opencv2/core.hpp>
#include <tuple> 
namespace vsl
{
 
    /// 估计相机运动
    /// @param img1 图像1
    /// @param img2 图像2
    /// @param camera_intrinsics 相机的内参，各分量分别为fx,fy,cx,cy。
    std::tuple<Eigen::Matrix3d, Eigen::Vector3d> estimate_motion(cv::Mat const &img1, cv::Mat const &img2, Eigen::Vector4d camera_intrinsics);
}
