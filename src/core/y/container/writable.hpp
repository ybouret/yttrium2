

//! \file

#ifndef Y_Container_Writable_Included
#define Y_Container_Writable_Included 1

#include "y/container/readable.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Writable container interface
    //
    //
    //__________________________________________________________________________
    template <typename T> class Writable : public Readable<T>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(T,Type); //!< aliases
        using Readable<T>::size;
        using Readable<T>::getItemAt;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        //! initialize
        inline explicit Writable() noexcept : Readable<T>() {}

    public:
        //! cleanup
        inline virtual ~Writable() noexcept {}

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! access when mutable
        /**
         \param indx in [1..size()]
         \return reference at indx
         */
        inline Type & operator[](const size_t indx) noexcept
        {
            assert(indx>0); assert(indx<=size());
            return Coerce(getItemAt(indx));
        }

        //! access when const
        /**
         \param indx in [1..size()]
         \return const reference at indx
         */
        inline ConstType & operator[](const size_t indx) const noexcept
        {
            assert(indx>0); assert(indx<=size());
            return getItemAt(indx);
        }

        //! load the same value \param value value to load
        inline void ld(ParamType value)
        {
            Writable<T> &a = *this;
            const size_t n = a.size();
            for(size_t i=1;i<=n;++i)
                a[i] = value;
        }

    private:
        Y_Disable_Copy_And_Assign(Writable); //!< discarding
    };

}

#endif

