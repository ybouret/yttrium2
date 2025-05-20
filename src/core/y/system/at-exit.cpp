
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
            Function func; //!< function
            void *   args; //!< persistent data
            Priority prio; //!< priority

            //! comparison by increasing priority
            static inline int Compare(const void * const lhs,
                                      const void * const rhs) noexcept
            {
                assert( 0 != lhs );
                assert( 0 != rhs );
                const Priority &l = static_cast<const Code *>(lhs)->prio;
                const Priority &r = static_cast<const Code *>(rhs)->prio;
                return (l<r) ? -1 : ( (r<l) ? 1 : 0);
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

        void AtExit:: Perform(Function       func,
                              void * const   args,
                              const Priority prio)
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
                if(prio == AtExitQueue[i].prio)
                    throw Specific::Exception(fn,"multiplie priority %u", unsigned(prio));
            }

            // limited count
            if(AtExitCount>=AtExit::Capacity)
                throw Specific::Exception(fn,"exceeded capacity=%u", unsigned(AtExit::Capacity));

            // build new code
            {
                AtExit::Code &code = AtExitQueue[AtExitCount++];
                code.func = func;
                code.args = args;
                code.prio = prio;
            }

            // keep ordered
            qsort(AtExitQueue, AtExitCount, sizeof(AtExit::Code), AtExit::Code::Compare);
        }


    }
}
