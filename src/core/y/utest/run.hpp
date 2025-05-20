
//! \file

#ifndef Y_UTest_Run_Included
#define Y_UTest_Run_Included 1

#include "y/exception.hpp"
#include "y/core/setup.hpp"
#include "y/utest/catch.hpp"
#include <iostream>
#include <iomanip>

namespace Yttrium
{

    //! start a int NAME(argc,argv)
#define Y_UTEST(NAME) \
/**/  int Y_UTest_##NAME(int argc, char **argv) \
/**/  {\
/**/    (void) argc;\
/**/    static const char * const program = argv[0];\
/**/    (void) program; \
/**/    {\
/**/      try\
/**/      {

    //! finish test code
#define Y_UDONE() \
/**/      }\
/**/      Y_UTEST_CATCH();\
/**/    }\
/**/  }

    namespace UTest
    {
        //______________________________________________________________________
        //
        //
        //! helper to display unsigned fields
        //
        //______________________________________________________________________
        struct Display
        {
            static size_t Width; //!< aligment value

            //! display value
            /**
             \param name value name, aligned on Width
             \param size value size
             */
            static void   Value(const char * const name, const size_t size);
        };
    }

    //! helper to display sizeof
#define Y_SIZEOF(NAME) do { UTest::Display::Value( "sizeof(" #NAME ")",sizeof(NAME)); } while(false)

    //! helper to display value
#define Y_PRINTV(NAME) do { UTest::Display::Value( #NAME, NAME); } while(false)

}

#endif

