
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
        template <typename T, size_t N = 1>
        class Workspace
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const size_t Capacity = N; //!< alias

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
            item(0),
            wksp()
            {
                Coerce(data) = static_cast<T *>( Y_Memory_BZero(wksp) );
                Coerce(item) = data-1;
            }



            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            T * const data; //!< address of workspace
            T * const item; //!< C++ address

        private:
            Y_Disable_Copy_And_Assign(Workspace);                      //!< discarding
            void *    wksp[ Alignment::WordsGEQ<sizeof(T)*N>::Count ]; //!< internal memory
        };

    }

}

#endif


