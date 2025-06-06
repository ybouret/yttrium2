
#include "y/concurrent/singulet.hpp"
#include <iostream>
#include <iomanip>

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
                std::cerr << '[' << std::setw(24) << identifier << ' ' << '@' << std::setw(5) <<  longevity << ' ' << ']';
                std::cerr << std::endl;
            }
            catch(...)
            {

            }
        }

    }
}
