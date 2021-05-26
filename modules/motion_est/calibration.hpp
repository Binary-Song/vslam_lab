#pragma once
#include <Eigen/Core>
#include <Eigen/StdVector>
#include <Eigen/Dense>
#include <Eigen/QR>
#include <cassert>
#include <iostream>

namespace vsl
{
    /// 标定摄像机，返回相机内参
    /// @param uv 一个2维列向量组，第i个向量表示第i个参照点的像素坐标
    /// @param xyz 一个3维列向量组，第i个向量表示第i个参照点的世界坐标
    /// @param e 相机的外参，默认为单位矩阵。
    /// @return 返回4维向量(fx,fy,cx,cy)
    Eigen::Vector4d calibrate_camera(Eigen::Matrix2Xd uv, Eigen::Matrix3Xd xyz, Eigen::Matrix4d e);
 
    Eigen::Vector4d calib_random_test_case(Eigen::MatrixXd const &uv,
                                           Eigen::MatrixXd const &xyz,
                                           Eigen::MatrixXd const &e,
                                           int picked_count);
} // namespace vsl
