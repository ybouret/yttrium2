
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


    std::ostream  & XMLog:: operator()(void)
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


    void XMLog:: Section:: init(const bool partial)
    {
        if(xml.verbose)
        {
            xml() << "<" << *str;
            if(!partial) xml.quit();
        }
        ++xml.depth;
    }

    void XMLog:: quit()
    {
        os << ">" << std::endl;
    }

}

