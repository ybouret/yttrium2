//! \file

#ifndef Y_Associative_Included
#define Y_Associative_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{

    template <typename KEY, typename T>
    class Associative
    {
    public:
        Y_Args_Expose(T,Type);
        Y_Args_Declare(KEY,Key);

    protected:
        inline explicit Associative() noexcept {}

    public:
        inline virtual ~Associative() noexcept;

    private:
        Y_Disable_Copy_And_Assign(Associative);
    };

}

#endif

