
#include "y/system/at-exit.hpp"
#include "y/exception.hpp"

#include <cassert>
#include <iostream>
#include <cstdlib>
#include <cstring>

namespace Yttrium
{
    namespace System
    {

        //! encapsulate calls
        struct AtExit:: Code
        {
            Function  func; //!< function
            void *    args; //!< persistent data
            Longevity life; //!< priority

            //! comparison by decreasing lifetime
            static inline int Compare(const void * const lhs,
                                      const void * const rhs) noexcept
            {
                assert( 0 != lhs );
                assert( 0 != rhs );
                const Longevity &l = static_cast<const Code *>(lhs)->life;
                const Longevity &r = static_cast<const Code *>(rhs)->life;
                return (l<r) ? 1 : ( (r<l) ? -1 : 0);
            }
        };

        static bool         AtExitRegister = true;           //!< global once flag
        static size_t       AtExitCount    = 0;              //!< global count
        static AtExit::Code AtExitQueue[ AtExit::Capacity ]; //!< global queue

        //! cleanup
        static inline void  AtExitClear() noexcept
        {
            memset(AtExitQueue,0,sizeof(AtExitQueue));
            AtExitCount = 0;
        }

        //! call function in decreasing priority
        static inline void AtExitCallback() noexcept
        {

            while(AtExitCount-- > 0)
            {
                AtExit::Code &code = AtExitQueue[AtExitCount];
                try
                {
                    code.func(code.args);
                }
                catch(...)
                {
                    
                }
            }

            AtExitClear();
        }

        void AtExit:: Perform(Function        func,
                              void * const    args,
                              const Longevity life)
        {
            static const char fn[] = "AtExit::Perform";
            assert( 0 != func);

            // must register once
            if(AtExitRegister)
            {
                if( 0 != atexit(AtExitCallback) )
                    throw Specific::Exception(fn,"Unable to use atexit()");
                AtExitRegister = false;
                AtExitClear();
            }

            // no multiple priority
            for(size_t i=0;i<AtExitCount;++i)
            {
                if(life == AtExitQueue[i].life)
                    throw Specific::Exception(fn,"multiplie longevities %u", unsigned(life));
            }

            // limited count
            if(AtExitCount>=AtExit::Capacity)
                throw Specific::Exception(fn,"exceeded capacity=%u", unsigned(AtExit::Capacity));

            // build new code
            {
                AtExit::Code &code = AtExitQueue[AtExitCount++];
                code.func = func;
                code.args = args;
                code.life = life;
            }

            // keep ordered
            qsort(AtExitQueue, AtExitCount, sizeof(AtExit::Code), AtExit::Code::Compare);
        }


    }
}
