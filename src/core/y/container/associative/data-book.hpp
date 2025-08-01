
//! \file


#ifndef Y_Associative_DataBook_Included
#define Y_Associative_DataBook_Included 1

#include "y/container/associative/hash/map.hpp"

namespace Yttrium
{
    class DataBook
    {
    public:
        explicit DataBook();
        virtual ~DataBook() noexcept;

    private:
        class Code;
        Y_Disable_Assign(DataBook);
        Code * const code;
    };
}

#endif

