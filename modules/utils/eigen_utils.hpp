#pragma once
#include <Eigen/Dense>
#include <algorithm>
#include <random>
#include <string>
#include "utils.hpp"
namespace vsl
{

    template <typename Derived>
    auto normalize_homogeneous(Eigen::MatrixBase<Derived> const &v)
    {
        assert(v.cols() == 3 && v.rows() == 1 && "Argument v has to be a 3d vector!");
        return v / v(2, 0);
    }

    inline auto random_permutation(size_t size)
    {
        std::random_device rd;
        std::mt19937 g(rd());

        Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> perm(size);
        perm.setIdentity();

        std::shuffle(perm.indices().data(), perm.indices().data() + perm.indices().size(), g);
        return perm;
    }


}