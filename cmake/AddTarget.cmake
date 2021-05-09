include(CMakeParseArguments)
#[[ example:


AddTarget(
    exe       有`exe`选项表示要生成可执行文件，没有表示要生成静态库 
    name      目标名
    src       源文件1 源文件2 ...
    includes  包含路径1 包含路径2 ... 
    libs      链接目标1 链接目标2 ...
    depends   依赖模块1 依赖模块2 ...
)

依赖模块 X 表示增加包含路径 X_INCLUDE_DIRS，并增加链接目标 X_LIBRARIES。
现在如果X_INCLUDE_DIRS为空，则自动调用find_package(X)找。

]] 
function(AddTarget)
    cmake_parse_arguments(
        "arg"                        # prefix
        "exe"                        # optional args
        "name"                       # one value args
        "libs;includes;src;depends"  # multi value args
        ${ARGN}
    )

    if(arg_exe)
        add_executable("${arg_name}" ${arg_src})
    else()
        add_library("${arg_name}" ${arg_src})
    endif()

    set(Includes "${arg_includes}")
    set(Libs "${arg_libs}")

    foreach(_dep   ${arg_depends})

        if(NOT ${_dep}_INCLUDE_DIRS )
            message("package `${_dep}` seems yet to be found, trying find_package .. ")
            find_package(${_dep} REQUIRED)
        endif() 

        list(APPEND Includes "${${_dep}_INCLUDE_DIRS}") 
        message("${${_dep}_LIBRARIES}")
        list(APPEND Libs     "${${_dep}_LIBRARIES}")
        
    endforeach(_dep arg_depends)

    message("i=${Includes}")
    message("l=${Libs}")

    target_include_directories("${arg_name}" PUBLIC ${Includes})
    target_link_libraries("${arg_name}" PUBLIC ${Libs})



endfunction(AddTarget) 