#include "y/utest/run.hpp"

using namespace Yttrium;

namespace {


    static inline int GetValue(const int trial)
    {
        if(trial<=0) throw Exception("Bad Trial");
        return trial;
    }

    static
    void Prototype(const int trial)
    {
        static const int inner = GetValue(trial);

        std::cerr << "inner = " << inner << std::endl;
    }

}

Y_UTEST(static_init)
{
    try {
        Prototype(0);
    }
    catch(const Exception &e)
    {
        e.show(std::cerr);
    }
    catch(...)
    {
        std::cerr << "Unhandled Exception" << std::endl;
        return 1;
    }

    Prototype(1);
    Prototype(2);

}
Y_UDONE()
