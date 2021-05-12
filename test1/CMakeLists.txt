
# add target
AddTarget(
    exe
    name      test1
    src       main.cpp 
    depends   fmt Eigen3 Sophus
    libs      opencv::opencv
) 
