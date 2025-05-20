
//! \file

#ifndef Y_Memory_Workspace_Included
#define Y_Memory_Workspace_Included 1

#include "y/memory/stealth.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace Memory
    {

        template <typename T>
        class Workspace
        {
        public:
            inline virtual ~Workspace() noexcept { Y_Memory_BZero(wksp); Coerce(data) = 0; }

        protected:
            inline explicit Workspace() noexcept :
            data(0),
            wksp()
            {
                Coerce(data) = static_cast<T *>( Y_Memory_BZero(wksp) );
            }

            T * const data;
        private:
            void *    wksp[ Alignment::WordsFor<T>::Count ];
        };

    }

}

#endif


