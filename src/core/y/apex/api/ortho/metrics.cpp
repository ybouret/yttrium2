
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
            dimensions(dims)
            {
                if(dimensions<1) throw Specific::Exception("Ortho::Metrics","nul dimension");
            }

            Metrics:: Metrics(const Metrics &_) noexcept :
            dimensions(_.dimensions)
            {
            }

            
        }
        
    }
    
}
