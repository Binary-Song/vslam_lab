cmake_minimum_required(VERSION 3.14)
project(___ProjectName___)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/3rdparty" "${CMAKE_CURRENT_LIST_DIR}/cmake")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/3rdparty")

# includes
include(AddTarget)

# install conan dependencies  
execute_process(
    COMMAND "conan" "install" ".."  "-s" "build_type=${CMAKE_BUILD_TYPE}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/3rdparty"
)

# find packages
find_package(fmt REQUIRED)
AddTarget(
    exe  
    name      main
    src       main.cpp 
    depends   fmt
)