
#include "y/string/env/convert.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(string_env_conv)
{
    const char name[] = "N";
    const size_t N = EnvironmentConvert::To<size_t>(name,100);

    std::cerr << name << " = " << N << std::endl;

}
Y_UDONE()
