#include "y/xml/attribute.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(xml_attribute)
{
    int a = 2;

    std::cerr << XML::Attribute("a",a) << XML::Attribute("a",a,5) << std::endl;

}
Y_UDONE()

