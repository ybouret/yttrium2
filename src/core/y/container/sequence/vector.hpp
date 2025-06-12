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

#define Y_Vector_Ctor() \
Sequence<T,DynamicContainer>(), \
Contiguous<Writable,T>(), \
THREADING_POLICY(),\
built(0)


    template <typename T, typename THREADING_POLICY = SingleThreadedClass>
    class Vector :
    public Sequence<T,DynamicContainer>,
    public Contiguous<Writable,T>,
    public THREADING_POLICY
    {
    public:
        Y_ARGS_DECL(T,Type);
        typedef SingleThreadedClass::Lock Lock;

        inline explicit Vector() noexcept :
        Y_Vector_Ctor(),
        code(0) {}

        inline explicit Vector(const WithAtLeast_ &, const size_t n) :
        Y_Vector_Ctor(),
        code( n>0 ? new Code(n) : 0)
        {
        }

        inline virtual ~Vector() noexcept
        {
            release_();
        }

        inline friend std::ostream & operator<<(std::ostream &os, const Vector &self)
        {
            volatile Lock guard(self);
            const Readable<T> &readable = self;
            return os << readable;
        }

        // interface
        virtual size_t size() const noexcept
        {
            Y_Must_Lock();
            return built;
        }

        virtual size_t capacity() const noexcept
        {
            Y_Must_Lock();
            return code ? code->count : 0;
        }

        virtual size_t available() const noexcept
        {
            Y_Must_Lock();
            return code ? code->count-built : 0;
        }

        virtual void reserve(const size_t n)
        {
            Y_Must_Lock();
            if(n>0)
            {
                if(0==code)
                {
                    code = new Code(n);
                }
                else
                {
                    // TODO: check overflow
                    Code * temp = new Code(n+code->count);  assert(temp->count>code->count);
                    Memory::Stealth::Copy(temp->entry,code->entry,built*sizeof(T));
                    delete code;
                    code = temp;
                }
            }
        }

        virtual void pushTail(ParamType args)
        {
            Y_Must_Lock();
            if(0==code)
                intoNewCode(args);
            else
            {
                if(built<code->count)
                    new (code->entry+built) T(args);
                else
                {
                    Code * temp = new Code( this->NextCapacity(built) );  assert(temp->count>built);
                    new (temp->entry+built) T(args);
                    Memory::Stealth::Copy(temp->entry,code->entry,built*sizeof(T));
                    delete code;
                    code = temp;
                }
            }
            ++built;
        }

        virtual void pushHead(ParamType args)
        {
            Y_Must_Lock();
            if(0==code)
                intoNewCode(args);
            else
            {
                const size_t filled = built * sizeof(T);
                if(built<code->count)
                {
                    MutableType * const curr = code->entry;
                    MutableType * const next = curr+1;
                    Memory::Stealth::Move(next,curr,filled);
                    Memory::Stealth::Zero(curr,sizeof(T));
                    try
                    {
                        new (code->entry) T(args);
                    }
                    catch(...)
                    {
                        Memory::Stealth::Move(curr,next,filled);
                        Memory::Stealth::Zero(code->entry+built,sizeof(T));
                        throw;
                    }
                }
                else
                {
                    Code * temp = new Code( this->NextCapacity(built) );  assert(temp->count>built);
                    new (temp->entry) T(args);
                    Memory::Stealth::Copy(temp->entry+1,code->entry,filled);
                    delete code;
                    code = temp;
                }
            }
            ++built;
        }

        virtual void free()    noexcept { free_();    }
        virtual void release() noexcept { release_(); }


    private:
        Y_Disable_Copy_And_Assign(Vector);
        size_t built;

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

        inline void intoNewCode(ConstType &args)
        {
            assert(0==code);
            assert(0==built);
            code = new Code(  this->NextCapacity(0) ); assert(code->count>0);
            new (code->entry) T(args);
        }

        virtual ConstType & getItemAt(const size_t indx) const noexcept
        {
            Y_Must_Lock();
            assert(0!=code);
            assert(indx>=1);
            assert(indx<=built);
            assert(built<=code->count);
            return code->cxx[indx];
        }

        inline void free_() noexcept
        {
            Y_Must_Lock();
            while(built>0) {
                assert(0!=code);
                Memory::Stealth::DestructedAndZeroed(& code->entry[built--]);
            }
        }

        inline void release_() noexcept
        {
            Y_Must_Lock();
            if(!code) { assert(!built); return; };
            free_(); Destroy(code);
        }


    };

}

#endif

