//! \file

#ifndef Y_Vector_Included
#define Y_Vector_Included 1

#include "y/object/school-of.hpp"
#include "y/container/sequence.hpp"
#include "y/container/dynamic.hpp"
#include "y/container/contiguous.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/type/args.hpp"
#include "y/type/with-at-least.hpp"
#include "y/memory/stealth.hpp"
#include "y/type/destroy.hpp"
#include "y/type/destruct.hpp"
#include "y/calculus/safe-add.hpp"

namespace Yttrium
{

    typedef Dynamic<Releasable> VectorContainer; //!< base class for vector

    //__________________________________________________________________________
    //
    //
    //! helper for common vector constructor part
    //
    //__________________________________________________________________________
#define Y_Vector_Ctor()         \
Container(),                    \
Sequence<T,VectorContainer>(),  \
Contiguous< Writable<T> >(),    \
ThreadingPolicy(),              \
built(0)

    //__________________________________________________________________________
    //
    //
    //
    //! Vector of homogeneous objects
    //
    //
    //______________________________________________________________________
    template <typename T, typename ThreadingPolicy = SingleThreadedClass>
    class Vector :
    public Sequence<T,VectorContainer>,
    public Contiguous< Writable<T> >,
    public ThreadingPolicy
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(T,Type);                 //!< aliases
        typedef SingleThreadedClass::Lock Lock; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup empty
        inline explicit Vector() noexcept :
        Y_Vector_Ctor(),
        code(0) {}

        //! setup with memory for at least n objects
        /**
         \param n minimal objects to be held
         */
        inline explicit Vector(const WithAtLeast_ &, const size_t n) :
        Y_Vector_Ctor(),
        code( n>0 ? new Code(n) : 0)
        {
        }

        //! setup with new () T(param)
        /**
         \param n      number of objects
         \param param argument for object constructor
         */
        inline explicit Vector(const size_t n, ParamType param) :
        Y_Vector_Ctor(),
        code( n>0 ? new Code(n) : 0)
        {
            try {
                for(size_t i=n;i>0;--i) {
                    new (code->entry+built) T(param);
                    ++built;
                }
            }
            catch(...) { release_(); throw; }
        }

        //! duplicate \param other another vector
        inline Vector(const Vector &other) :
        Y_Vector_Ctor(),
        code( 0 )
        {
            const size_t n = other.size();
            if( n > 0 )
            {
                code = new Code(n);
                try {
                    for(size_t i=1;i<=n;++i) {
                        new (code->entry+built) T( other[i] );
                        ++built;
                    }
                }
                catch(...)
                {
                    release_(); throw;
                }
            }
        }

        //! cleanup
        inline virtual ~Vector() noexcept {
            release_();
        }


        //! forward display to Readable<T>
        /**
         \param os output stream
         \param self *this
         \return output stream
         */
        inline friend std::ostream & operator<<(std::ostream &os, const Vector &self)
        {
            volatile Lock guard(self);
            const Readable<T> &readable = self;
            return os << readable;
        }

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual size_t size() const noexcept
        {
            Y_Must_Lock();
            return built;
        }

        //! [GradualContainer] \return capacity
        virtual size_t capacity() const noexcept
        {
            Y_Must_Lock();
            return code ? code->maxBlocks : 0;
        }

        //! [GradualContainer] \return available
        virtual size_t available() const noexcept
        {
            Y_Must_Lock();
            return code ? code->maxBlocks-built : 0;
        }

        //! [Dynamic Container] reserve \param n extra room for n objects
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
                    Code * temp = new Code( Calculus::SafeAdd(n,code->maxBlocks) );
                    assert(temp->maxBlocks>code->maxBlocks);
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
                if(built<code->maxBlocks)
                    new (code->entry+built) T(args);
                else
                {
                    Code * temp = new Code( this->NextCapacity(built) );  assert(temp->maxBlocks>built);
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
                if(built<code->maxBlocks)
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
                    Code * temp = new Code( this->NextCapacity(built) );  assert(temp->maxBlocks>built);
                    new (temp->entry) T(args);
                    Memory::Stealth::Copy(temp->entry+1,code->entry,filled);
                    delete code;
                    code = temp;
                }
            }
            ++built;
        }

        virtual void popTail() noexcept
        {
            Y_Must_Lock();
            popTail_();
        }


        virtual void popHead() noexcept
        {
            Y_Must_Lock();
            assert(0!=code);
            assert(built>0);
            T * const target = code->entry;
            Destruct(target);
            Memory::Stealth::Move(target,target+1, --built*sizeof(T) );
            Memory::Stealth::Zero(target+built,sizeof(T));
        }


        virtual void free()    noexcept { free_();    }
        virtual void release() noexcept { release_(); } //!< [Releasable] release all memory


    private:
        Y_Disable_Assign(Vector); //!< discarding
        size_t built;             //!< currently built

        typedef Memory::SchoolOf<MutableType> SchoolType; //!< alias

        //______________________________________________________________________
        //
        //! managing memory
        //______________________________________________________________________
        class Code : public Object, public SchoolType
        {
        public:
            //! get memory \param minimalCapacity passed to allocator
            explicit Code(size_t minimalCapacity) :
            Object(), SchoolType(minimalCapacity)
            {
            }

            //! cleanup
            inline virtual ~Code() noexcept {}

        private:
            Y_Disable_Copy_And_Assign(Code); //!< discarding
        };
        
        Code * code; //!< implementation

        //! build object into new code with minimal capacity \param args constructor argument
        inline void intoNewCode(ConstType &args)
        {
            assert(0==code);
            assert(0==built);
            code = new Code(  this->NextCapacity(0) ); assert(code->maxBlocks>0);
            new (code->entry) T(args);
        }

        //! [Readable] \param indx in [1:built] \return indx-th object
        virtual ConstType & getItemAt(const size_t indx) const noexcept
        {
            Y_Must_Lock();
            assert(0!=code);
            assert(indx>=1);
            assert(indx<=built);
            assert(built<=code->maxBlocks);
            return code->cxx[indx];
        }

        //! remove existing tail object
        inline void popTail_() noexcept
        {
            assert(0!=code);
            assert(built>0);
            Memory::Stealth::DestructedAndZeroed(& code->entry[--built]);
        }

        //! destruct all objects, keep memory
        inline void free_() noexcept
        {
            Y_Must_Lock();
            while(built>0) popTail_();
        }

        //! destruct all objects and all memory
        inline void release_() noexcept
        {
            Y_Must_Lock();
            if(!code) { assert(!built); return; };
            free_(); Destroy(code);
        }

        //! [Sequence] \return head iterm
        virtual ConstType & getHead() const noexcept {
            Y_Must_Lock();
            assert(0!=code);
            assert(built>0);
            return code->entry[0];
        }

        //! [Sequence] \return tail item
        virtual ConstType & getTail() const noexcept {
            Y_Must_Lock();
            assert(0!=code);
            assert(built>0);
            return code->cxx[built];
        }

    };

}

#endif

