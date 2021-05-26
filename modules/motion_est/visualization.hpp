#pragma once
#include "utils.hpp"

#ifdef EXPORTING_VIS
#define VIS_API __declspec(dllexport)
#else
#define VIS_API __declspec(dllimport)
#endif


namespace vsl
{
    VIS_API void visualize_path(vsl::Vectors3d const& pts);

} // namespace vsl
