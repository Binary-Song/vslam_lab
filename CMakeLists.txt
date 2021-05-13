cmake_minimum_required(VERSION 3.14)
project(___ProjectName___)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/3rdparty" "${CMAKE_CURRENT_LIST_DIR}/cmake")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/3rdparty")
 
# includes
include(AddTarget)
include(InstallConanPackages)
include(CppGlobalConfig)

# config cpp
CppGlobalConfig(
    std 11
    others_flags  mysmvcflag1 mysmvcflag2
    clang_flags xxx
    others_defs  mymsvcdef=aaa mymsvcdef=bbb
    gnu_defs    xxx
    intel_flags xxx
)

# install conan dependencies and find packages
InstallConanPackages(
    "${CMAKE_CURRENT_LIST_DIR}"
    output                  "${CMAKE_CURRENT_LIST_DIR}/3rdparty"
    packages_to_find        "fmt"
) 

# add target
AddTarget(
    exe
    name      main
    src       "./main.cpp" 
    depends   fmt 
)

