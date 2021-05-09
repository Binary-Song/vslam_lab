cmake_minimum_required(VERSION 3.14)
project(___ProjectName___)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/3rdparty")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/3rdparty")

# install conan dependencies  
execute_process(
    COMMAND "conan" "install" ".."  "-s" "build_type=${CMAKE_BUILD_TYPE}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/3rdparty"
)

#
find_package(fmt REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC ${fmt_LIBRARIES})
target_include_directories(main PUBLIC ${fmt_INCLUDE_DIRS})

message("${fmt_LIBRARIES} ddd ${fmt_INCLUDE_DIRS}")