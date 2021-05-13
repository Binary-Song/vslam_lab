#[[   

CppGlobalConfig(  
    [std                   STANDARD]
    [<compiler_id>_flags   FLAG...] 
    [flags                 FLAG...]
    [<compiler_id>_defs    MACRO...] 
    [defs                  MACRO...] 
)

std
    编译时采用的C++标准，例如：11 14 17 等。该值直接被写入CMAKE_CXX_STANDARD中。

<compiler_id>_flags
    使用特定编译器时采用的编译选项。可以为不同的编译器指定不同的编译选项。<compiler_id>是*全部小写*的编译器标识符。例如想指定MSVC编译器使用的编译选项，这里就是`msvc_flags`；想指定GCC的，这里就是`gnu_flags`，具体参考CMAKE_CXX_COMPILER_ID。

flags
    如果<compiler_id>_flags参数没有一个指定当前编译器应该使用什么编译选项，则使用本参数指定的编译选项。

    例：
    CppGlobalConfig(
        std                  11
        msvc_flags           /utf-8 
        gnu_flags            -Wall -Werror
        flags                -Wall
    )

    则对MSVC，编译选项为/utf-8，对gcc，编译选项为-Wall -Werror，对其他编译器，编译选项为-Wall。

<compiler_id>_defs
    使用特定编译器采用的宏定义。格式为`XXX`或者`XXX=YYY`。具体参见add_compile_definitions()的说明。

defs
    如果<compiler_id>_defs参数没有一个指定当前编译器应该使用什么宏定义，则使用本参数指定的宏定义。

]] 
function(CppGlobalConfig)


# 处理<compiler_id>_x相关任务。
# x 目前可能是"flags"或者"defs"。因为过程类似，所以把过程封装起来。 
# argv 是CppGlobalConfig的实参。
macro(handle_x   x  argv)
    # 以下注释假设x为"flags" 
    # 预处理参数，找到<compiler_id>_flags参数中出现的所有compiler_id，放在compiler_ids中。
    # <compiler_id>_flags本身放在argnames中。
    set(compiler_ids "")
    set(argnames     "") 
    set(match_regex "^.*_${x}$")
    set(replace_regex "_${x}$")

    foreach(arg ${argv}) 
        if(${arg} MATCHES ${match_regex})
            set(argcpy  "${arg}")
            string(REGEX REPLACE "${replace_regex}" "" compilerId "${argcpy}")
            list(APPEND compiler_ids "${compilerId}")
            list(APPEND argnames "${arg}")
        endif()
    endforeach()

    # message("compiler ids = ${compiler_ids}")
    # message("arg names = ${argnames}")
    # 进行参数分析，分析出来的参数都带arg_前缀
    cmake_parse_arguments(
        "arg"                       # prefix
        ""                          # optional args
        ""                          # one value args
        "${argnames};${x}"          # multi value args
        ${argv}
    )
    string(TOLOWER "${CMAKE_CXX_COMPILER_ID}" comiler_id_lower_case)
    # message("arg_${comiler_id_lower_case}_${x} = ${arg_${comiler_id_lower_case}_${x}}")
    set(out_values "${arg_${comiler_id_lower_case}_${x}}")
    if(NOT out_values)
        set(out_values "${arg_${x}}")
    endif()
    set(out_unparsed "${arg_UNPARSED_ARGUMENTS}")
endmacro()

# 求差集
function(set_diff S T out)
    list(APPEND S_minus_T ${S})
    list(REMOVE_ITEM S_minus_T ${T})
    set(${out} "${S_minus_T}" PARENT_SCOPE)
endfunction()

# 求并集 
function(set_union S T out)
    list(APPEND union_list ${S} ${T})
    list(REMOVE_DUPLICATES union_list)
    set(${out} "${union_list}" PARENT_SCOPE)
endfunction()

# 求对称差
function(set_symdiff S T out)
    set_diff("${S}" "${T}" s_minus_t)
    set_diff("${T}" "${S}" t_minus_s)
    set_union("${s_minus_t}" "${t_minus_s}" symdiff)
    set(${out} "${symdiff}" PARENT_SCOPE)
endfunction()

# 求交集
function(set_intersect S T out)
    set_union("${S}" "${T}" s_u_t)
    set_symdiff("${S}" "${T}" s_d_t)
    set_diff("${s_u_t}" "${s_d_t}" itsc)
    set(${out} "${itsc}" PARENT_SCOPE)
endfunction()

handle_x(flags "${ARGV}")
add_compile_options(${out_values})
if(out_values)
message("flags += ${out_values}")
endif()
set(flags_unparsed "${out_unparsed}")

handle_x(defs "${ARGV}")
add_compile_definitions(${out_values})
if(out_values)
message("defs += ${out_values}")
endif() 
set(defs_unparsed "${out_unparsed}")


cmake_parse_arguments(
    "arg"                       # prefix
    ""                          # optional args
    "std"                          # one value args
    ""          # multi value args
    ${ARGV}
)

set_intersect("${flags_unparsed}" "${defs_unparsed}" u1)
set_intersect("${u1}" "${arg_UNPARSED_ARGUMENTS}" never_parsed_args)

if(never_parsed_args)
    message(FATAL_ERROR "unknown args: ${never_parsed_args}")
endif()


if(arg_std) 
    set(CMAKE_CXX_STANDARD ${arg_std} PARENT_SCOPE) 
    set(CMAKE_CXX_STANDARD_REQUIRED ON PARENT_SCOPE) 
    set(CMAKE_CXX_EXTENSIONS OFF PARENT_SCOPE)
endif()




#[[ 
    foreach(arg ${ARGV}) 
        if(${arg} MATCHES "^.*_flags$")
            string(REGEX MATCH "^.*_flags$" argcpy ${arg})
            string(REGEX REPLACE "_flags$"
            "" compilerId
            "${argcpy}")
            list(APPEND compiler_ids "${compilerId}")
            list(APPEND argnames    "${arg}")
        endif()
    endforeach()

    message("compiler ids = ${compiler_ids}")
    message("arg names = ${argnames}")

    # args
 
    cmake_parse_arguments(
        "arg"                       # prefix
        ""                          # optional args
        "std"                       # one value args
        "${argnames};flags;defs"              # multi value args
        ${ARGN}
    )

    string(TOLOWER "${CMAKE_CXX_COMPILER_ID}" comiler_id_lower_case)

    set(the_flags "${arg_${comiler_id_lower_case}_flags}")
 
    if(NOT the_flags)
        set(the_flags "${arg_flags}")
    endif()

    message("compile flags added: ${the_flags}")
    add_compile_options(${the_flags})


    set(the_defs "${arg_${comiler_id_lower_case}_defs}")

    if(NOT the_defs)
        set(the_defs "${arg_others_defs}")
    endif()
        

     
    message("compile defs added: ${the_defs}")
        add_compile_definitions(${the_defs})

    if(arg_std) 
        set(CMAKE_CXX_STANDARD ${arg_std} PARENT_SCOPE) 
        set(CMAKE_CXX_STANDARD_REQUIRED ON PARENT_SCOPE) 
        set(CMAKE_CXX_EXTENSIONS OFF PARENT_SCOPE)
    endif()

    if(MSVC)
        add_compile_options(${arg_msvc_flags})
    else()
        add_compile_options(${arg_flags})
    endif() 
        add_compile_definitions(${arg_defs})
]] 
endfunction(CppGlobalConfig)
