
//! \file

#ifndef Y_UTest_Catch_Included
#define Y_UTest_Catch_Included 1

//! helper to catch exceptions
#define Y_UTEST_CATCH()\
/**/     catch(const Yttrium::Exception &e) {\
/**/        e.show(std::cerr); return 1;\
/**/      }\
/**/      catch(const std::exception &e) {\
/**/        std::cerr << "*** " << e.what() << std::endl;  return 2;\
/**/      }\
/**/      catch(...) {\
/**/        std::cerr << Core::Unknown << ' ' << Exception::CallSign << std::endl;\
/**/        return 3;\
/**/      }\
/**/    return 0

#endif

