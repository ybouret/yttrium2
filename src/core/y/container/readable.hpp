
//! \file

#ifndef Y_Container_Readable_Included
#define Y_Container_Readable_Included 1

#include "y/container.hpp"
#include "y/type/args.hpp"
namespace Yttrium
{

    template <typename T> class Readable : public Container
    {
    public:
        Y_ARGS_EXPOSE(T,Type);

    protected:
        inline explicit Readable() noexcept : Container() {}

    public:
        inline virtual ~Readable() noexcept {}

        inline ConstType & operator[](const size_t indx) const noexcept
        {
            assert(indx>0); assert(indx<=size());
            return getItemAt(indx);
        }

    private:
        Y_Disable_Copy_And_Assign(Readable);
        
    protected:
        virtual ConstType & getItemAt(const size_t indx) const noexcept = 0;
    };

}

#endif

