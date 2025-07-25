
#include "y/apex/api/ortho/metrics.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Apex
    {
        namespace Ortho
        {

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
    
}
