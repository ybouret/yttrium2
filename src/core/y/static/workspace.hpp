
//! \file

#ifndef Y_Static_Workspace_Included
#define Y_Static_Workspace_Included 1

#include "y/memory/stealth.hpp"
#include "y/calculus/alignment.hpp"


namespace Yttrium
{
    namespace Static
    {

        //______________________________________________________________________
        //
        //
        //
        //! inline blank workspace for given type
        //
        //
        //______________________________________________________________________
        template <typename T, size_t N = 1>
        class Workspace
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

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



            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            T * const data; //!< address of workspace

        private:
            Y_Disable_Copy_And_Assign(Workspace);                      //!< discarding
            void *    wksp[ Alignment::WordsGEQ<sizeof(T)*N>::Count ]; //!< internal memory
        };

    }

}

#endif
