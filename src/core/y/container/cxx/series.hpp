//! \file

#ifndef Y_Container_Cxx_Series_Included
#define Y_Container_Cxx_Series_Included 1

#include "y/container/contiguous.hpp"
#include "y/object/school-of.hpp"
#include "y/memory/stealth.hpp"
#include "y/container/gradual.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! in-memory fixed capacity
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class CxxSeries : public Contiguous< Writable<T> >, public Gradual
    {
    public:
        Y_Args_Declare(T,Type);

        inline CxxSeries(const size_t capa) : built(0),  data(capa) {}

        inline CxxSeries(const CxxSeries &arr) : built(0), data(arr.built)
        {
            try {
                while(built<arr.built) {
                    new (data.entry+built) Type(arr.data.entry[built]);
                    ++built;
                }
            }
            catch(...) { free_(); throw; }
        }

        CxxSeries & operator<<(ParamType args) {
            assert(size()<capacity());
            new (data.entry+built) Type(args);
            ++built;
            return *this;
        }


        inline virtual ~CxxSeries() noexcept
        {
            free_();
        }


        inline virtual size_t size()      const noexcept { return built; }
        inline virtual void   free()            noexcept { free_(); }
        inline virtual size_t capacity()  const noexcept { return data.maxBlocks; }
        inline virtual size_t available() const noexcept { return data.maxBlocks - built; }

    private:
        Y_Disable_Assign(CxxSeries);
        size_t                        built;
        Memory::SchoolOf<MutableType> data;

        inline void free_() noexcept {
            while(built) Memory::Stealth::DestructedAndZeroed( &data.entry[--built] );
        }

        inline virtual ConstType & getItemAt(const size_t indx) const noexcept
        {
            assert(indx>0);
            assert(indx<=data.maxBlocks);
            return data.cxx[indx];
        }
    };

}

#endif
