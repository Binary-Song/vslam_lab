#include "calibration.hpp"
#include <cassert>
#include <Eigen/QR>
#include <iostream>
#include <Eigen/Dense>
#include "eigen_utils.hpp"

namespace vsl
{

    Eigen::Vector4d calibrate_camera(Eigen::Matrix2Xd uv, Eigen::Matrix3Xd xyz, Eigen::Matrix4d e)
    {
        assert(uv.rows() == 2 && "Pixel coordinates have 2 dimensions!");
        assert(xyz.rows() == 3 && "World coordinates have 3 dimensions!");
        assert(uv.cols() == xyz.cols() && "If uv has x columns, then xyz should have x columns too!");
        assert(e.rows() == 4 && e.cols() == 4 && "Extrinstics e should be a 4*4 matrix!");

        auto cols = uv.cols();
        Eigen::Matrix4Xd xyz_h(4, cols);
        xyz_h.topRows(3) = xyz.topRows(3);
        xyz_h.bottomRows(1) = Eigen::MatrixXd::Ones(1, cols);

        Eigen::MatrixXd xyz_cam = (e * xyz_h);

        // 构造A
        Eigen::MatrixXd A(cols * 2, 4);
        for (int i = 0; i < cols; i++)
        {
            // xi 0 zi 0
            A(i, 0) = xyz_cam(0, i);
            A(i, 1) = 0;
            A(i, 2) = xyz_cam(2, i);
            A(i, 3) = 0;
        }
        for (int i = 0; i < cols; i++)
        {
            // 0 yi 0 zi
            A(cols + i, 0) = 0;
            A(cols + i, 1) = xyz_cam(1, i);
            A(cols + i, 2) = 0;
            A(cols + i, 3) = xyz_cam(2, i);
        }

        // 构造b
        Eigen::MatrixXd b(cols * 2, 1);
        for (int i = 0; i < cols; i++)
        {
            b(i) = xyz_cam(2, i) * uv(0, i);
        }
        for (int i = 0; i < cols; i++)
        {
            b(cols + i) = xyz_cam(2, i) * uv(1, i);
        }

        Eigen::Vector4d x = A.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b).cast<double>();
        return x;
    }
 

    Eigen::Vector4d calib_random_test_case(Eigen::MatrixXd const &uv,
                                           Eigen::MatrixXd const &xyz,
                                           Eigen::MatrixXd const &e,
                                           int used)
    {
        auto p1 = vsl::random_permutation(uv.cols());
        auto uv_mat = (uv * p1).leftCols(used);
        auto xyz_mat = (xyz * p1).leftCols(used);
        Eigen::Vector4d K = vsl::calibrate_camera(uv_mat, xyz_mat, e);
        return K;
    }

    /*
       template <typename UV, typename XYZ, typename E>
    Eigen::Vector4d calibrateCamera_templated(Eigen::MatrixBase<UV> const &uv,
                         Eigen::MatrixBase<XYZ> const &xyz,
                         Eigen::MatrixBase<E> const &e)
    {
       
        STATIC_ASSERT_ROWS_EQ(UV, 2, "Pixel coordinates have 2 dimensions!");
        assert(uv.rows() == 2 && "Pixel coordinates have 2 dimensions!");

        STATIC_ASSERT_ROWS_EQ(XYZ, 3, "World coordinates have 3 dimensions!");
        assert(xyz.rows() == 3 && "World coordinates have 3 dimensions!");

        static_assert(UV::ColsAtCompileTime == XYZ::ColsAtCompileTime ||
                          UV::ColsAtCompileTime == -1 ||
                          XYZ::ColsAtCompileTime == -1,
                      "If uv has x columns, then xyz should have x columns too!");
        assert(uv.cols() == xyz.cols() && "If uv has x columns, then xyz should have x columns too!");

        STATIC_ASSERT_ROWS_EQ(E, 4, "Extrinstics e should be a 4*4 matrix!");
        STATIC_ASSERT_COLS_EQ(E, 4, "Extrinstics e should be a 4*4 matrix!");
        assert(e.rows() == 4 && e.cols() == 4 && "Extrinstics e should be a 4*4 matrix!");
    

        auto cols = uv.cols();
        Eigen::Matrix4Xd xyz_h(4, cols);
        xyz_h.topRows(3) = xyz.topRows(3);
        xyz_h.bottomRows(1) = Eigen::MatrixXd::Ones(1, cols);
 
        Eigen::MatrixXd xyz_cam = (e * xyz_h);
 
        // 构造A
        Eigen::MatrixXd A(cols * 2, 4);
        for (int i = 0; i < cols; i++)
        {
            // xi 0 zi 0
            A(i, 0) = xyz_cam(0, i);
            A(i, 1) = 0;
            A(i, 2) = xyz_cam(2, i);
            A(i, 3) = 0;
        }
        for (int i = 0; i < cols; i++)
        {
            // 0 yi 0 zi
            A(cols + i, 0) = 0;
            A(cols + i, 1) = xyz_cam(1, i);
            A(cols + i, 2) = 0;
            A(cols + i, 3) = xyz_cam(2, i);
        }

        // 构造b
        Eigen::MatrixXd b(cols * 2, 1);
        for (int i = 0; i < cols; i++)
        {
            b(i) = xyz_cam(2, i) * uv(0, i);
        }
        for (int i = 0; i < cols; i++)
        {
            b(cols + i) = xyz_cam(2, i) * uv(1, i);
        }
        
        Eigen::Vector4d x = A.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b).cast<double>();
        return x;
    }
    
    
    */
}