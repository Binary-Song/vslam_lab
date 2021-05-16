# add target
AddTarget(
    exe
    verbose
    name      test3
    src       "main.cpp"  "./bow3demo.cpp"
    depends   pangolin g2o dbow3  
    bin_dir   "${PROJECT_SOURCE_DIR}/3rdparty/bin" 
)  