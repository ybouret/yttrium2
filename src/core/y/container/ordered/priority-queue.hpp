//! \file

#ifndef Y_PriorityQueue_Included
#define Y_PriorityQueue_Included 1


#include "y/container/ordered.hpp"
#include "y/container/dynamic.hpp"
#include "y/container/ordered/prio-queue.hpp"
#include "y/object/school-of.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/calculus/safe-add.hpp"
#include "y/type/with-at-least.hpp"
#include "y/static/moniker.hpp"
#include "y/static/replica.hpp"

namespace Yttrium
{

    typedef Dynamic<Releasable> PriorityQueuePolicy; //!< memory management

    //__________________________________________________________________________
    //
    //
    //
    //! Dynamic Priority Queue
    //
    //
    //__________________________________________________________________________
    template <
    typename T,
    typename Comparator      = Sign::Comparator<T>,
    typename ThreadingPolicy = SingleThreadedClass>
    class PriorityQueue : public Ordered<T,PriorityQueuePolicy>, public ThreadingPolicy
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef Memory::SchoolOf<T> SchoolType;      //!< alias
        typedef PrioQueue<T>        PQueueType;      //!< alias
        Y_Args_Declare(T,Type);                      //!< aliases
        typedef typename ThreadingPolicy::Lock Lock; //!< alias;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup empty
        inline explicit PriorityQueue() noexcept : code(0), compare() {}

        //! setup with minimal capacity \param n minimal capacity
        inline explicit PriorityQueue(const WithAtLeast_ &, const size_t n) :
        code( n>0 ? new Code(n) :  0 ), compare()
        {
        }


        //! cleanup
        inline virtual ~PriorityQueue() noexcept { release_(); }

        //! duplicate \param other another queue
        inline PriorityQueue(const PriorityQueue &other) : code(0), compare()
        {
            Y_Must_Lock();
            if(other.code && other.code->size) code = new Code( *other.code );
        }

        //! display \param os output stream \param self *this \return os
        inline friend std::ostream & operator<<(std::ostream &os, const PriorityQueue &self)
        {
            if(self.code) os << *self.code; else os << Core::Nil;
            return os;
        }


        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
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

        //! [Releasable] release all memory
        inline virtual void release() noexcept { release_(); }

        inline virtual void reserve(const size_t n)
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
                    code->push(args,compare);
                else
                {
                    Static::Replica<Type>       replica(args);
                    {
                        Code * const temp = new Code( this->NextCapacity(code->capacity) );
                        temp->steal(*code);
                        delete code;
                        code = temp;
                    }
                    assert(code->size<code->capacity);
                    replica.yield(code->tree+code->size);
                    code->balance(compare);
                }
            }
            else
            {
                code = new Code( this->NextCapacity(0) );
                assert(code->size<code->capacity);
                code->push(args,compare);
            }
        }

        //! \return top item
        inline virtual ConstType & peek() const noexcept
        {
            assert(0!=code);
            assert(code->size>0);
            return code->entry[0];
        }

        //______________________________________________________________________
        //
        //
        // methods
        //
        //______________________________________________________________________

        //! \return number of swaps during insertion
        inline size_t nswp() const noexcept
        {
            return code ? code->nswp : 0;
        }

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________

    private:
        class Code; Code * code; //!< internal code
    public:
        Comparator         compare; //!< comparator

    private:
        Y_Disable_Assign(PriorityQueue); //!< aliases

        //! release code
        inline void release_() noexcept {
            Y_Must_Lock();
            if(code) { delete code; code=0; }
        }

        //______________________________________________________________________
        //
        //
        //! memory+pqueue
        //
        //______________________________________________________________________
        class Code :  public SchoolType, public PQueueType
        {
        public:
            using SchoolType::entry;
            using SchoolType::maxBlocks;
            using PQueueType::size;

            //! setup \param minimalCapacity desired capacity
            inline Code(const size_t minimalCapacity) :
            SchoolType(minimalCapacity),
            PQueueType(entry,maxBlocks)
            {
            }

            //! copy using object copy constructor \param other another code
            inline Code(const Code &other) :
            SchoolType(other.size),
            PQueueType(entry,maxBlocks)
            {
                while(size<other.size) {
                    new (entry+size) T(other.entry[size]);
                    ++size;
                }
            }

            //! cleanup
            inline virtual ~Code() noexcept {}

        private:
            Y_Disable_Assign(Code); //!< discarding
        };
    };

}


#endif // !Y_PriorityQueue_Included
