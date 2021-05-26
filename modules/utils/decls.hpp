namespace vsl
{
    template <class T>
    using Vectors = std::vector<T, Eigen::aligned_allocator<T>>;
    using Vectors2d = Vectors<Eigen::Vector2d>;
    using Vectors3d = Vectors<Eigen::Vector3d>;
    using Vectors4d = Vectors<Eigen::Vector4d>;
}