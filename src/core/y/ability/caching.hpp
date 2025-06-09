
//! \file

#ifndef Y_Caching_Included
#define Y_Caching_Included 1

#include "y/ability/collectable.hpp"

namespace Yttrium
{

    class Caching : public Collectable
    {
    protected:
        explicit Caching() noexcept;
    public:
        virtual ~Caching() noexcept;

        virtual void   cache(const size_t n)  = 0;
        virtual size_t count() const noexcept = 0;
        
    private:
        Y_Disable_Copy_And_Assign(Caching);
    };

}

#endif
