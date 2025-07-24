
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

        //! setup with default value
        /**
         \param num number of created object
         */
        inline explicit CxxArray(const size_t num) : code( new Code(num) )
        {
        }

        //! setup with same value
        /**
         \param num number of created object
         \param arg argument for each constructor
         */
        inline explicit CxxArray(const size_t num, ParamType arg) : code( new Code(num,arg) )
        {
        }

        //! duplicate \param other another array
        inline CxxArray(const CxxArray &other) :
        Container(), Contiguous< Writable<T> >(),
        code( new Code(*other.code) )
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
        Y_Disable_Assign(CxxArray); //!< discarding
        class Code;
        Code * code; //!< current code


        //______________________________________________________________________
        //
        //
        //! inline implementation
        //
        //______________________________________________________________________
        class Code : public Object, public Memory::SchoolOf<MutableType>, public Memory::Operating<MutableType>
        {
        public:
            typedef  Memory::SchoolOf<MutableType>  ScType;
            typedef  Memory::Operating<MutableType> OpType;
            using ScType::entry;

            //! setup \param count default objects
            inline Code(const size_t count) :
            Object(),
            ScType(count),
            OpType(entry,count)
            {
            }

            //! setup
            /**
             \param count from constructor
             \param arg from constructor
             */
            inline Code(const size_t count, ConstType &arg) :
            Object(),
            ScType(count),
            OpType(CopyOf,arg,entry,count)
            {
            }

            //! cleanup
            inline virtual ~Code() noexcept { }

            //! duplicate \param other another code
            inline Code(const Code &other) :
            Object(),
            ScType(other.count),
            OpType(entry,other.entry,other.count)
            {
            }

        private:
            Y_Disable_Assign(Code); //!< discarding

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

