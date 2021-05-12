
# add target
AddTarget(
    exe
    name      test2
    src       main.cpp 
    depends   fmt Eigen3 Sophus
    libs      opencv::opencv
) 