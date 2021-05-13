#[[   

CppGlobalConfig(  
    [std         c++标准版本(11 14 17 20等)]
    [msvc_flags  MSVC编译选项1 MSVC编译选项2 ...] 
    [flags       其他编译器编译选项1 其他编译器编译选项2 ...]
    [defs        宏定义1 宏定义2 ...]
)

例：
CppGlobalConfig(
    std  11
    msvc_flags 
)

]] 
function(CppGlobalConfig)
message("args ${ARGV}")

    set(compiler_ids "")
    set(arg_names     "")

    foreach(arg ${ARGV}) 
        if(${arg} MATCHES "^.*(_flags$|_defs$)")
            string(REGEX MATCH "^.*(_flags$|_defs$)" argcpy ${arg})
            string(REGEX REPLACE "(_flags$|_defs$)"
            "" compilerId
            "${argcpy}")
            list(APPEND compiler_ids "${compilerId}")
            list(APPEND argnames    "${arg}")
        endif()
    endforeach()

    #message("compiler ids = ${compiler_ids}")
    #message("arg names = ${argnames}")


    # args
 
    cmake_parse_arguments(
        "arg"                       # prefix
        ""                          # optional args
        "std"                       # one value args
        "${argnames}"              # multi value args
        ${ARGN}
    )
    
    if(arg_UNPARSED_ARGUMENTS)
        message( "unrecognized argument(s): ${arg_UNPARSED_ARGUMENTS}")
    endif()

    string(TOLOWER "${CMAKE_CXX_COMPILER_ID}" comiler_id_lower_case)

    set(the_flags "${arg_${comiler_id_lower_case}_flags}")
    set(the_defs "${arg_${comiler_id_lower_case}_defs}")
 
    if(NOT the_flags)
        set(the_flags "${arg_others_flags}")
    endif()

    if(NOT the_defs)
        set(the_defs "${arg_others_defs}")
    endif()
        
    message("compile flags added: ${the_flags}")
        add_compile_options(${the_flags})
     
    message("compile defs added: ${the_defs}")
        add_compile_definitions(${the_defs})

    if(arg_std) 
        set(CMAKE_CXX_STANDARD ${arg_std} PARENT_SCOPE) 
        set(CMAKE_CXX_STANDARD_REQUIRED ON PARENT_SCOPE) 
        set(CMAKE_CXX_EXTENSIONS OFF PARENT_SCOPE)
    endif()

    if(MSVC)
        add_compile_options("/utf-8")
        add_compile_options(${arg_msvc_flags})
    else()
        add_compile_options(${arg_flags})
    endif() 
        add_compile_definitions(${arg_defs})
#]] 
endfunction(CppGlobalConfig)
