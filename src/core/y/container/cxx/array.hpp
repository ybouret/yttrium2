
//! \file

#ifndef Y_Container_Cxx_Array_Included
#define Y_Container_Cxx_Array_Included 1

#include "y/container/contiguous.hpp"
#include "y/object/school-of.hpp"
#include "y/memory/operating.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{

    template <typename T>
    class CxxArray : public Contiguous< Writable<T> >
    {
    public:
        Y_ARGS_DECL(T,Type);
        inline explicit CxxArray(const size_t num, ParamType arg) : code( new Code(num,arg) )
        {
        }

        inline virtual ~CxxArray() noexcept { assert(0!=code); Destroy(code); }

        virtual size_t size() const noexcept { assert(0!=code); return code->numBlocks; }

    private:
        Y_Disable_Copy_And_Assign(CxxArray);
        class Code;
        Code * code;


        class Code : public Object, public Memory::SchoolOf<T>, public Memory::Operating<T>
        {
        public:
            using Memory::SchoolOf<T>::entry;
            
            inline Code(const size_t num, ConstType &arg) :
            Object(),
            Memory::SchoolOf<T>(num),
            Memory::Operating<T>(CopyOf,arg,entry,num)
            {
            }

            inline virtual ~Code() noexcept
            {
            }
        private:
            Y_Disable_Copy_And_Assign(Code);

        };

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

