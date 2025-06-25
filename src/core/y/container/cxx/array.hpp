
//! \file

#ifndef Y_Container_Cxx_Array_Included
#define Y_Container_Cxx_Array_Included 1

#include "y/container/contiguous.hpp"
#include "y/object/school-of.hpp"
#include "y/memory/operating.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! in-memory fixed size() container
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class CxxArray : public Contiguous< Writable<T> >
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

        //! setup with same value
        /**
         \param num number of created object
         \param arg argument for each constructor
         */
        inline explicit CxxArray(const size_t num, ParamType arg) : code( new Code(num,arg) )
        {
        }

        //! cleanup
        inline virtual ~CxxArray() noexcept { assert(0!=code); Destroy(code); }

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        //! [Container] \return fixed size
        virtual size_t size() const noexcept { assert(0!=code); return code->numBlocks; }

    private:
        Y_Disable_Copy_And_Assign(CxxArray); //!< discarding
        class Code;
        Code * code; //!< current code


        //______________________________________________________________________
        //
        //
        //! inline implementation
        //
        //______________________________________________________________________
        class Code : public Object, public Memory::SchoolOf<T>, public Memory::Operating<T>
        {
        public:
            using Memory::SchoolOf<T>::entry;

            //! setup
            /**
             \param num from constructor
             \param arg from constructor
             */
            inline Code(const size_t num, ConstType &arg) :
            Object(),
            Memory::SchoolOf<T>(num),
            Memory::Operating<T>(CopyOf,arg,entry,num)
            {
            }

            //! cleanup
            inline virtual ~Code() noexcept { }

        private:
            Y_Disable_Copy_And_Assign(Code); //!< discarding

        };

        //! [Readable] \param indx object index \return memory emplacement
        virtual ConstType & getItemAt(const size_t indx) const noexcept
        {
            assert(0!=code);
            assert(indx>=1);
            assert(indx<=code->numBlocks);
            return code->cxx[indx];
        }
    };

}

#endif

