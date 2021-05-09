cmake_minimum_required(VERSION 3.14)
project(vslam_lab)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/3rdparty" "${CMAKE_CURRENT_LIST_DIR}/cmake")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/3rdparty")

# includes
include(AddTarget)

# install conan dependencies  
execute_process(
    COMMAND "conan" "install" ".."  "-s" "build_type=${CMAKE_BUILD_TYPE}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/3rdparty"
    RESULT_VARIABLE STATUS
)

if(NOT STATUS EQUAL 0)
    message(FATAL_ERROR "Error occurred install conan dependencies. (return code: ${STATUS})")
endif()

# find packages

AddTarget(
    exe  
    name      main
    src       main.cpp 
    depends   fmt Eigen3 Sophus
)