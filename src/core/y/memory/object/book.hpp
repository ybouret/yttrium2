//! \file

#ifndef Y_Memory_Book_Included
#define Y_Memory_Book_Included 1


#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {
        
        class Book
        {
        public:
            explicit Book() noexcept;
            virtual ~Book() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Book);
        };
    }

}

#endif

