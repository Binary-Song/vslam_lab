#include <string>
#include <iostream>
 
#define DEBUG_PRINT(x) debug_print(x, #x)
#define DEBUG_PRINTS(x,s) debug_print(x, #x,s)
 
template <typename T>
inline void debug_print(T const &x, std::string title)
{
    std::cout
        << title << "=" << std::endl
        << x << std::endl;
}

template <typename T>
inline void debug_print(T const &x, std::string title, std::ostream &strm)
{
    strm
        << title << "=" << std::endl
        << x << std::endl;
}
