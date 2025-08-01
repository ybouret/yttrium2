#include "y/coven/analysis.hpp"
#include "y/string/percent.hpp"


namespace Yttrium
{
    namespace Coven
    {
        unsigned           Analysis::Width    = 8;
        const char * const Analysis::CallSign = "Coven::Analysis";
        const char * const Analysis::And      = "&&";
        const char * const Analysis::Filter   = "Filter";


        void Analysis:: Summary(XMLog &        xml,
                                const Tribes & tribes,
                                const size_t   generated,
                                const Survey & survey)
        {
            Y_XML_Section(xml,"Summary");
            const apn used = tribes.cardinal - generated;
            Y_XMLog(xml, "#configuration  : " << std::setw(Width)  << tribes.cardinal);
            Y_XMLog(xml, "#generated      : " << std::setw(Width)  << generated << " [" << StringPercent::APGet(used,tribes.cardinal) << " compression]" );
            Y_XMLog(xml, "#issuedVectors  : " << std::setw(Width)  << survey.calls);
            Y_XMLog(xml, "#uniqueVectors  : " << std::setw(Width)  << survey->size << " [" << StringPercent::Get(survey->size,survey.calls) << "  efficiency]");
        }



        void Analysis:: FilterOut(XMLog &xml, const size_t oldSize, const size_t newSize)
        {
            Y_XMLog(xml, "#initial  : " << std::setw(Width) << oldSize);
            Y_XMLog(xml, "#selected : " << std::setw(Width) << newSize << " [" << StringPercent::Get(newSize,oldSize) << " matching]");
        }

    }
}
