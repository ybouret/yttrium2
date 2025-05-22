
//! \file

#ifndef Y_Memory_Workspace_Included
#define Y_Memory_Workspace_Included 1

#include "y/memory/stealth.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! inline workspace for given type
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Workspace
        {
        public:

            //! cleanup
            inline virtual ~Workspace() noexcept { Y_Memory_BZero(wksp); Coerce(data) = 0; }

        protected:

            //! initialize
            inline explicit Workspace() noexcept :
            data(0),
            wksp()
            {
                Coerce(data) = static_cast<T *>( Y_Memory_BZero(wksp) );
            }

            T * const data; //!< address of workspace
        private:
            Y_Disable_Copy_And_Assign(Workspace);            //!< discarding
            void *    wksp[ Alignment::WordsFor<T>::Count ]; //!< internal memory
        };

    }

}

#endif


