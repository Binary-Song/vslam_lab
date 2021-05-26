# add target

AddTarget(
    exe
    name      ceres_testing
    src       "./ceres_test.cpp"
    depends   Ceres OpenCV
    bin_dir   "${PROJECT_SOURCE_DIR}/3rdparty/bin" 
)

AddTarget(
    exe
    name      hand_write_GN
    src       "./guass-newton.cpp"
    depends   OpenCV Eigen3
    bin_dir   "${PROJECT_SOURCE_DIR}/3rdparty/bin" 
)

AddTarget(
    exe
    name     g2o_testing
    src      "./g2o_test.cpp"
    depends  g2o OpenCV
    bin_dir   "${PROJECT_SOURCE_DIR}/3rdparty/bin"  
)