

#include "y/stream/xmlog.hpp"
#include "y/utest/run.hpp"
#include "y/string/env.hpp"

using namespace Yttrium;

Y_UTEST(stream_xmlog)
{

    bool  verbose = Environment::Flag("VERBOSE");
    XMLog xml(std::cerr,verbose);

    Y_XMLog(xml, "Hello XMLog!");

    Y_XML_Section(xml,"toto");
    Y_XMLog(xml,"blah blah");
    {
        Y_XML_Section(xml,"titi");
        Y_XMLog(xml,"blah blah, blah");

    }

}
Y_UDONE()

