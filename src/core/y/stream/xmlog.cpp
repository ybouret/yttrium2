
#include "y/stream/xmlog.hpp"

namespace Yttrium
{
    XMLog:: XMLog(std::ostream &output, bool &verbosity) noexcept :
    verbose(verbosity),
    depth(0),
    os(output)
    {

    }

    XMLog:: ~XMLog() noexcept
    {

    }


    std::ostream  & XMLog:: operator()(void) noexcept
    {
        return XML::Indent(os,depth);
    }


    XMLog:: Section:: ~Section() noexcept
    {
        --xml.depth;
        if(str)
        {
            if(xml.verbose) xml() << "</" << *str << ">" << std::endl;
            delete str;
        }
    }


    void XMLog:: Section:: init()
    {
        if(xml.verbose) xml() << "<" << *str << ">" << std::endl;
        ++xml.depth;
    }

}

