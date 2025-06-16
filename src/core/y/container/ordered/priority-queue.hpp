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

        inline explicit PriorityQueue() noexcept : code(0), compare() {}
        inline virtual ~PriorityQueue() noexcept { release_(); }


        inline PriorityQueue(const PriorityQueue &other) : code(0), compare()
        {
            Y_Must_Lock();
            if(other.code && other.code->size) code = new Code( *other.code );
        }

        inline virtual size_t size()      const noexcept {
            Y_Must_Lock();
            return code ? code->size : 0;
        }

        inline virtual size_t capacity()  const noexcept {
            Y_Must_Lock();
            return code ? code->capacity : 0;
        }

        inline virtual size_t available() const noexcept {
            Y_Must_Lock();
            return code ? code->capacity - code->size : 0;
        }

        inline virtual void free()    noexcept {
            Y_Must_Lock();
            if(code) code->free();
        }

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
        Y_Disable_Assign(PriorityQueue);

        inline void release_() noexcept {
            Y_Must_Lock();
            if(code) { delete code; code=0; }
        }

        class Code : public Object, public SchoolType, public PQueueType
        {
        public:
            using SchoolType::entry;
            using SchoolType::count;
            using PQueueType::size;

            //! setup \param minimalCapacity desired capacity
            inline Code(const size_t minimalCapacity) :
            Object(),
            SchoolType(minimalCapacity),
            PQueueType(entry,count)
            {
            }

            //! copy using object copy constructor \param other another code
            inline Code(const Code &other) :
            Object(),
            SchoolType(other.size),
            PQueueType(entry,count)
            {
                while(size<other.size) {
                    new (entry+size) T(other.entry[size]);
                    ++size;
                }
            }



            inline virtual ~Code() noexcept {}


        private:
            Y_Disable_Assign(Code);
        };
    };

}


#endif
