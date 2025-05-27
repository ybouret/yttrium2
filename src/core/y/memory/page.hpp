//! \file

#ifndef Y_Memory_Page_Included
#define Y_Memory_Page_Included


#include "y/system/compiler.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //! Anonymous Page header to be used in list
        //
        //______________________________________________________________________
        struct Page
        {
            Page *next; //!< for list
            Page *prev; //!< for list

            //! clear a page
            /**
             \param page a valid memory page
             \param bytes its size
             \return memset(page,0,bytes)
             */
            static void * Addr(Page * const page, const size_t bytes) noexcept;

            //! format address to be store in list
            /**
             \param addr a valid memory page to store
             \return memset(addr,0,sizeof(Page))
             */
            static Page * Cast(void * const addr) noexcept;
        };
    }

}

#endif

