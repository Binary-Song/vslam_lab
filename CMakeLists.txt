cmake_minimum_required(VERSION 3.14)
project(vslam_lab)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/3rdparty" "${CMAKE_CURRENT_LIST_DIR}/cmake")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/3rdparty")

# includes
include(AddTarget)
include(InstallConanPackages)
include(CppGlobalConfig)

# config cpp
CppGlobalConfig(
    std         17 
    msvc_flags  /utf-8 
    msvc_defs   -D_USE_MATH_DEFINES
) 

# install conan dependencies and find packages
InstallConanPackages(
    "${CMAKE_CURRENT_LIST_DIR}"
    output                  "${CMAKE_CURRENT_LIST_DIR}/3rdparty"
    packages_to_find        "fmt;Eigen3;Sophus;OpenCV;Boost;Pangolin;g2o" 
)

add_subdirectory(test1)
add_subdirectory(test2)
add_subdirectory(test3)

get_target_property(OUT test3 LINK_LIBRARIES)
get_target_property(OUT2 test3 INCLUDE_DIRECTORIES)
message(STATUS "lib to link against ${OUT}  includes ${OUT2}")
