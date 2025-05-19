
//! \file

#ifndef Y_UTest_Run_Included
#define Y_UTest_Run_Included 1

#include "y/exception.hpp"
#include "y/core/setup.hpp"
#include <cstdio>

namespace Yttrium
{

#define Y_UTEST(NAME) \
/**/  int Y_UTest_##NAME(int argc, char **argv) \
/**/  {\
/**/    (void) argc;\
/**/    static const char * const program = argv[0];\
/**/    (void) program; \
/**/    {\
/**/      try\
/**/      {

#define Y_UDONE() \
/**/      }\
/**/      catch(...) {\
/**/        std::cerr << Core::Unknown << ' ' << Exception::CallSign << std::endl;\
/**/        return 3;\
/**/      }\
/**/    }\
/**/    return 0;\
/**/  }


}

#endif

