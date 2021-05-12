function(CppGlobalConfig)

    # args
    cmake_parse_arguments(
        "arg"                        # prefix
        ""                        # optional args
        "std"                       # one value args
        ""  # multi value args
        ${ARGN}
    )
    if(arg_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "unrecognized argument(s): ${arg_UNPARSED_ARGUMENTS}")
    endif()

    # set default values of target properties
    set(CMAKE_CXX_STANDARD ${arg_std} PARENT_SCOPE) 
    set(CMAKE_CXX_STANDARD_REQUIRED ON PARENT_SCOPE) 
    set(CMAKE_CXX_EXTENSIONS OFF PARENT_SCOPE)
    
    if(MSVC)
        add_compile_options("/utf-8")
    endif() 
endfunction(CppGlobalConfig)
