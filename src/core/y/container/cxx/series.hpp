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
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(T,Type); //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param capa capacity
        inline CxxSeries(const size_t capa) : built(0),  data(capa) {}

        //! duplicate \param arr another series
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

        //! cleanup
        inline virtual ~CxxSeries() noexcept { free_(); }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! append \param args argument \return *this
        CxxSeries & operator<<(ParamType args) {
            assert(size()<capacity());
            new (data.entry+built) Type(args);
            ++built;
            return *this;
        }

        //! append with binary constructor
        /**
         \param u first arg
         \param v second arg
         \return *this
         */
        template <typename U, typename V>
        CxxSeries & push(U &u, V &v)
        {
            assert(size()<capacity());
            new (data.entry+built) Type(u,v);
            ++built;
            return *this;
        }


        //! append with ternary constructor
        /**
         \param u first  arg
         \param v second arg
         \param w third  arg
         \return *this
        */
        template <typename U, typename V, typename W>
        CxxSeries & push(U &u, V &v, W &w)
        {
            assert(size()<capacity());
            new (data.entry+built) Type(u,v,w);
            ++built;
            return *this;
        }

        //! append with quaternary constructor
        /**
         \param u first  arg
         \param v second arg
         \param w third  arg
         \param x fourth arg
         \return *this
         */
        template <typename U, typename V, typename W, typename X>
        CxxSeries & push(U &u, V &v, W &w, X &x)
        {
            assert(size()<capacity());
            new (data.entry+built) Type(u,v,w,x);
            ++built;
            return *this;
        }


        //! append with penternary constructor
        /**
         \param u first  arg
         \param v second arg
         \param w third  arg
         \param x fourth arg
         \param y fifth arg
         \return *this
         */
        template <typename U, typename V, typename W, typename X, typename Y>
        CxxSeries & push(U &u, V &v, W &w, X &x, Y &y)
        {
            assert(size()<capacity());
            new (data.entry+built) Type(u,v,w,x,y);
            ++built;
            return *this;
        }



        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual size_t size()      const noexcept { return built; }
        inline virtual void   free()            noexcept { free_(); }
        inline virtual size_t capacity()  const noexcept { return data.maxBlocks; }
        inline virtual size_t available() const noexcept { return data.maxBlocks - built; }

    private:
        Y_Disable_Assign(CxxSeries);         //!< discarding
        size_t                        built; //!< built object
        Memory::SchoolOf<MutableType> data;  //!< memory

        //! free all objects
        inline void free_() noexcept {
            while(built) Memory::Stealth::DestructedAndZeroed( &data.entry[--built] );
        }

        //! \param indx \return (*this)[indx]
        inline virtual ConstType & getItemAt(const size_t indx) const noexcept
        {
            assert(indx>0);
            assert(indx<=data.maxBlocks);
            return data.cxx[indx];
        }
    };

}

#endif
