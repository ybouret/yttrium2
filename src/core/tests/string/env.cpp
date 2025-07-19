#include "y/string/env.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(string_env)
{
    for (int i = 1; i < argc; ++i)
    {
        const char* const name = argv[i];
        String value;
        if (Environment::Get(value, name))
        {
            std::cerr << "[" << name << "]=[" << value << "]" << std::endl;
        }
        else
        {
            std::cerr << "undefined [" << name << "]" << std::endl;
        }
    }
}
Y_UDONE()
