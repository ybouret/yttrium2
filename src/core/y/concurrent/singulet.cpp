
#include "y/concurrent/singulet.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Concurrent
    {
        bool Singulet::Verbose = false;
        
        Singulet:: ~Singulet() noexcept
        {
        }

        Singulet:: Singulet() noexcept
        {
        }


        void Singulet:: Display(const char * const prefix,
                                const char * const identifier,
                                const Longevity    longevity) noexcept
        {
            try
            {
                if(prefix) std::cerr << prefix;
                std::cerr << '[' << identifier << '@' << longevity << ']';
            }
            catch(...)
            {

            }
        }

    }
}
