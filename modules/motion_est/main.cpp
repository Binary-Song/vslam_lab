#include "motion_est.hpp"
#include "eigen_utils.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <fmt/core.h>
#include "visualization.hpp"
#include <Eigen/Geometry>
#include <math.h>
int main(int argc, char **argv)
{

    vsl::Vectors2d uv;
    vsl::Vectors3d xyz;
    std::ifstream file(R"(D:\Projects\vslam_lab\data\mc\calibsample_data.txt)");
    std::string garbage;
    file >> garbage >> garbage >> garbage >> garbage >> garbage;

    double u, v, x, y, z;
    while (file >> u)
    {
        file >> v >> x >> y >> z;
        uv.push_back(Eigen::Vector2d(u, v));
        xyz.push_back(Eigen::Vector3d(x, y, z));
    }

    Eigen::Matrix<double, 2, -1> uv_mat(2, uv.size());
    Eigen::Matrix<double, 3, -1> xyz_mat(3, xyz.size());
    for (int i = 0; i < uv.size(); i++)
    {
        uv_mat.block<2, 1>(0, i) = uv[i];
    }
    for (int i = 0; i < xyz.size(); i++)
    {
        xyz_mat.block<3, 1>(0, i) = xyz[i];
    }

    auto R = Eigen::AngleAxisd(M_PI / 2, Eigen::Vector3d(1, 0, 0));
    auto T = Eigen::Translation3d(0, -1.62, 0);
    auto ex = (T * R).matrix();

    Eigen::Vector4d K = vsl::calibrate_camera(uv_mat, xyz_mat, ex);

    DEBUG_PRINT(K);

    

    auto new_uv = K * ex * xyz_mat;
    DEBUG_PRINT(new_uv);
    DEBUG_PRINT(uv_mat);

    cv::Mat old_frame = cv::imread(fmt::format("D:\\Projects\\vslam_lab\\data\\mc\\captures\\{}.jpg", 0));
    Eigen::Vector3d p(0, 0, 0);
    vsl::Vectors3d track;
    track.push_back(p);

    for (int i = 0; i < 424; i++)
    {
        cv::Mat new_frame = cv::imread(fmt::format("D:\\Projects\\vslam_lab\\data\\mc\\captures\\{}.jpg", i));
        auto &&[R, t] = vsl::estimate_motion(old_frame, new_frame, K);
        old_frame = new_frame;
        p = R.transpose() * (p - t).eval();
        track.push_back(p);

        Eigen::AngleAxisd aa(R);
        double angle = aa.angle() / M_PI * 180;
        auto axis = aa.axis();
        DEBUG_PRINT(axis);
    }
    vsl::visualize_path(track);
}
