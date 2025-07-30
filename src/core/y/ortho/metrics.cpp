
#include "y/ortho/metrics.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Ortho
    {

        const char * Metrics:: HumanReadableQuality(const Quality q) noexcept
        {
            switch(q)
            {
                    Y_Return_Named_Case(Basis);
                    Y_Return_Named_Case(HyperPlane);
                    Y_Return_Named_Case(Generating);
            }
            return Core::Unknown;
        }


        Metrics:: ~Metrics() noexcept
        {

        }


        Metrics:: Metrics(const size_t dims) :
        dimensions(dims),
        hyperplane(dims-1)
        {
            if(dimensions<1) throw Specific::Exception("Ortho::Metrics","nul dimension");
        }

        Metrics:: Metrics(const Metrics &_) noexcept :
        dimensions(_.dimensions),
        hyperplane(_.hyperplane)
        {
        }


        Quality Metrics:: qualify(const size_t size) const noexcept
        {
            if(size>=dimensions) return Basis;
            if(size>=hyperplane) return HyperPlane;
            return Generating;
        }


    }

}
