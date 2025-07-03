
//! \file

#ifndef Y_System_Program_Included
#define Y_System_Program_Included 1

#include "y/exception.hpp"
#include <iostream>
#include <iomanip>

#define Y_PROGRAM() \
/**/    int main(int argc, const char * argv[]) {\
/**/        (void)argc; const char * const program = argv[0];\
/**/        try

#define Y_EXECUTE() \
/**/        catch(const std::exception &excp) { std::cerr << excp.what() << std::endl; return 2; }\
/**/        catch(...) { std::cerr << "unhandled exception in " << program << std::endl; return 3; }\
/**/        return 0; \
/**/    }
#endif

