find_package(pangolin REQUIRED)
add_library(visualization SHARED "./visualization.cpp")
target_include_directories(visualization PUBLIC ".")
target_link_libraries(visualization PRIVATE  utils ${pangolin_LIBRARIES})
target_include_directories(visualization PRIVATE ${pangolin_INCLUDE_DIR} ) 
target_compile_options(visualization PRIVATE "-DEXPORTING_VIS")

AddTarget(
    exe 
    verbose
    name     motion_est 
    src      "./motion_est.cpp" "./calibration.cpp" "./main.cpp" "./feature_extract.cpp" 
    includes "." 
    libs     utils visualization
    depends  OpenCV Eigen3 fmt
    bin_dir   "${PROJECT_SOURCE_DIR}/3rdparty/bin"
)

