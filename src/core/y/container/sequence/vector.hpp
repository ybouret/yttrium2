//! \file

#ifndef Y_Vector_Included
#define Y_Vector_Included 1

#include "y/object/school-of.hpp"
#include "y/container/sequence.hpp"
#include "y/container/contiguous.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/type/args.hpp"
#include "y/type/with-at-least.hpp"
#include "y/memory/stealth.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{

    template <typename T, typename THREADING_POLICY = SingleThreadedClass>
    class Vector :
    public Sequence<T,DynamicContainer>,
    public Contiguous<Writable,T>,
    public THREADING_POLICY
    {
    public:
        Y_ARGS_DECL(T,Type);
        typedef SingleThreadedClass::Lock Lock;

        inline explicit Vector() : built(0), code(0) {}
        inline explicit Vector(const WithAtLeast_ &, const size_t n) :
        built(0), code( n>0 ? new Code(n) : 0)
        {
        }

        inline virtual ~Vector() noexcept
        {
            release_();
        }

        // interface
        virtual size_t size() const noexcept
        {
            Y_Must_Lock();
            return built;
        }

        virtual size_t capacity() const noexcept
        {
            return code ? code->count : 0;
        }

        virtual size_t available() const noexcept
        {
            return code ? code->count-built : 0;
        }

        virtual void reserve(const size_t n)
        {
            if(n>0)
            {
                if(0==code)
                {
                    code = new Code(n);
                }
                else
                {
                    // TODO: check overflow
                    Code * temp = new Code(n+code->count);
                    assert(temp->count>code->count);
                    Memory::Stealth::SafeCopy(temp->entry,code->entry,built*sizeof(T));
                    delete code;
                    code = temp;
                }
            }
        }


    private:
        Y_Disable_Copy_And_Assign(Vector);
        size_t built = 0;

        typedef Memory::SchoolOf<MutableType> SchoolType;
        class Code : public Object, public SchoolType
        {
        public:
            explicit Code(size_t minimalCapacity) :
            Object(), SchoolType(minimalCapacity)
            {
            }

            inline virtual ~Code() noexcept
            {
            }

        private:
            Y_Disable_Copy_And_Assign(Code);
        };
        Code * code;

        virtual ConstType & getItemAt(const size_t indx) const noexcept
        {
            assert(0!=code);
            assert(indx>=1);
            assert(indx<=built);
            assert(built<=code->count);
            return code->cxx[indx];
        }

        inline void free_() noexcept
        {
            while(built>0) {
                assert(0!=code);
                Memory::Stealth::DestructedAndZeroed(& code->entry[built--]);
            }
        }

        inline void release_() noexcept
        {
            if(!code) { assert(!built); return; };
            free_(); Destroy(code);
        }


    };

}

#endif

