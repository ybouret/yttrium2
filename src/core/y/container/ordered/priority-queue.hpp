//! \file

#ifndef Y_PriorityQueue_Included
#define Y_PriorityQueue_Included 1


#include "y/container/ordered.hpp"
#include "y/container/dynamic.hpp"
#include "y/container/ordered/prio-queue.hpp"
#include "y/object/school-of.hpp"
#include "y/threading/single-threaded-class.hpp"

namespace Yttrium
{

    template <
    typename T,
    typename Comparator      = Sign::Comparator<T>,
    typename ThreadingPolicy = SingleThreadedClass>
    class PriorityQueue : public Ordered<T,DynamicContainer>, public ThreadingPolicy
    {
    public:
        typedef Memory::SchoolOf<T> SchoolType;
        typedef PrioQueue<T>        PQueueType;
        using typename ThreadingPolicy::Lock;
        Y_ARGS_DECL(T,Type);

        explicit PriorityQueue() noexcept : code(0), compare() {}
        virtual ~PriorityQueue() noexcept { release_(); }

        inline virtual size_t size()      const noexcept { return code ? code->size : 0; }
        inline virtual size_t capacity()  const noexcept { return code ? code->capacity : 0; }
        inline virtual size_t available() const noexcept { return code ? code->capacity - code->size : 0; }

        inline virtual void free()    noexcept { if(code) code->free(); }
        inline virtual void release() noexcept { release_(); }
        inline virtual void reserve(size_t n)
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
                    Code * temp = new Code(n+code->count);
                    temp->steal(*code);
                    delete code;
                    code = temp;
                }
            }
        }

        inline virtual Type pop() {
            Y_Must_Lock();
            assert(0!=code);
            assert(code->size>0);
            return code->pop(compare);
        }

        inline virtual void push(ParamType args) {
            Y_Must_Lock();
            if(code)
            {
                if(code->size<code->capacity)
                {
                    code->push(args,compare);
                }
                else
                {
                    Code * temp = new Code( this->NextCapacity(code->capacity));
                    temp->steal(*code);
                    delete code;
                    code = temp;
                }
            }
            else
            {
                code = new Code( this->NextCapacity(0) );
                code->push(args,compare);
            }
        }

    private:
        class Code; Code * code;
    public:
        Comparator         compare;

    private:
        Y_Disable_Copy_And_Assign(PriorityQueue);

        inline void release_() noexcept {
            Y_Must_Lock();
            if(code) { delete code; code=0; }
        }

        class Code : public Object, public SchoolType, public PQueueType
        {
        public:
            inline explicit Code(const size_t minimalCapacity) :
            Object(),
            SchoolType(minimalCapacity),
            PQueueType(this->entry,this->count)
            {
            }

            inline virtual ~Code() noexcept {}


        private:
            Y_Disable_Copy_And_Assign(Code);
        };
    };

}


#endif
