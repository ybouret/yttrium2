#include "y/concurrent/nucleus.hpp"
#include "y/calculus/alignment.hpp"
#include "y/check/static.hpp"
#include "y/type/destruct.hpp"
#include "y/memory/stealth.hpp"
#include "y/exception.hpp"

#include <iostream>

namespace Yttrium
{

    namespace Concurrent
    {

        static void    * nucleusWorkspace[ Alignment::WordsFor<Nucleus>::Count ];
        static Nucleus * nucleus = 0;

        
        void Nucleus:: SelfDestruct(void *) noexcept
        {
            assert(0!=nucleus);
            nucleus->~Nucleus();
            nucleus = 0;
            Y_Memory_BZero(nucleusWorkspace);
        }

        Nucleus:: Nucleus() : Singulet()
        {
            if(Verbose) { std::cerr << '+' << CallSign << std::endl; }
        }

        Nucleus:: ~Nucleus() noexcept
        {
            if(Verbose) { std::cerr << '-' << CallSign << std::endl; }

        }

        const char * const Nucleus:: CallSign = "Concurrent::Nucleus";

        const char * Nucleus:: callSign() const noexcept
        {
            return CallSign;
        }

        Singulet::Longevity Nucleus:: lifeTime() const noexcept
        {
            return LifeTime;
        }


        Nucleus & Nucleus:: Instance()
        {
            Y_STATIC_CHECK(sizeof(nucleusWorkspace)>=sizeof(Nucleus),BadNucleusWorkspace);

            if(0==nucleus) {

                // create resources
                try
                {
                    nucleus =  new ( Y_Memory_BZero(nucleusWorkspace) ) Nucleus();
                }
                catch(...)
                {
                    Y_Memory_BZero(nucleusWorkspace);
                    nucleus = 0;
                    throw;
                }

                // register
                {
                    void * const args = 0;
                    try
                    {
                        System::AtExit::Perform(SelfDestruct,args,LifeTime);
                    }
                    catch(...)
                    {
                        SelfDestruct(args);
                        throw;
                    }
                }
            }


            return *nucleus;

        }

    }
}


