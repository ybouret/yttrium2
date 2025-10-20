#include "y/mkl/fit/samples.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            const char * const SamplesCommon:: CallSign = "Fit::Samples";
            
            SamplesCommon:: SamplesCommon() noexcept : vlist()
            {
                
            }


            SamplesCommon:: ~SamplesCommon() noexcept
            {
            }

            void SamplesCommon:: ErrorMultipleName(const String &id)
            {
                throw Specific::Exception(CallSign,"found multiple name '%s'", id.c_str());
            }
        }

    }

}

