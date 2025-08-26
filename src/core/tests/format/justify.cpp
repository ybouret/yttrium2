

#include "y/format/justify.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(format_justify)
{

    const String s = "hello";

    std::cerr << "|" << Justify(s,10,Justify::Left)   << "|" << std::endl;
    std::cerr << "|" << Justify(s,10,Justify::Right)  << "|" << std::endl;
    std::cerr << "|" << Justify(s,10,Justify::Center) << "|" << std::endl;


}
Y_UDONE()
