
//! \file

#ifndef Y_Light_Array_Included
#define Y_Light_Array_Included 1

#include "y/container/contiguous.hpp"
#include "y/check/usual.hpp"
#include "y/memory/stealth.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! C++ array from local persistent data
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class LightArray : public Contiguous< Writable<T> >
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Expose(T,Type);                      //!< aliases
        typedef Contiguous< Writable<T> > SelfType; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param arr address of first item \param num number of items
        inline LightArray(Type * const arr, const size_t num) noexcept :
        SelfType(),
        cxx( ((MutableType *) Memory::Stealth::Address(arr))-1 ),
        count(num)
        {
            assert( Good(arr,num) );
        }

        //! duplicate \param other another array
        inline LightArray(const LightArray &other) noexcept :
        Container(),
        SelfType(),
        cxx(other.cxx),
        count(other.count)
        {
        }

        //! cleanu[
        inline virtual ~LightArray() noexcept
        {
            Coerce(cxx)=0;
            Coerce(count)=0;
        }

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        //! \return initial count
        inline virtual size_t size() const noexcept { return count; }

    private:
        Y_Disable_Assign(LightArray); //!< discarding
        MutableType * const cxx;      //!< for [1..size()]
        const size_t        count;    //!< size

        //! \param i in [1..count] \return i-th object
        inline ConstType & getItemAt(const size_t i) const noexcept
        {
            return cxx[i];
        }
    };

}

#endif

