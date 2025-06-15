
#include "y/container.hpp"
#include "y/utest/run.hpp"

#include "y/memory/stealth.hpp"
#include "y/object.hpp"
#include "y/type/destruct.hpp"
#include "y/type/args.hpp"
#include "y/type/sign.hpp"

#include "y/check/usual.hpp"
#include "y/core/display.hpp"

#include "y/container/sequence/vector.hpp"

namespace Yttrium
{

#define heap_parent(npos) ((size_t)(((npos) - 1) / 2))
#define heap_left(npos) (((npos) * 2) + 1)
#define heap_right(npos) (((npos) * 2) + 2)

    template <typename T>
    class PrioQ : public Object
    {
    public:
        Y_ARGS_DECL(T,Type);

        explicit PrioQ(T * const    workspace,
                       const size_t numBlocks) noexcept :
        tree( workspace ),
        size( 0 ),
        capacity( numBlocks )
        {
            assert(Good(workspace,numBlocks));
            assert(Memory::Stealth::Are0(workspace,numBlocks*sizeof(T)));
        }


        virtual ~PrioQ() noexcept
        {
            assert(Good(tree,size));
            while(size>0)
                Destruct( &tree[--Coerce(size)] );
            Coerce(tree)     = 0;
            Coerce(capacity) = 0;
        }

        inline friend std::ostream & operator<<(std::ostream &os, const PrioQ &self)
        {
            return Core::Display(os,self.tree,self.size);
        }


        void steal(PrioQ &q) noexcept
        {
            assert(0==size);
            assert(capacity>=q.size);
            Memory::Stealth::SafeCopy(tree,q.tree, (Coerce(size) = q.size)*sizeof(T) );
            Coerce(q.size) = 0;
        }

        template <typename COMPARE>
        inline void push(ParamType value, COMPARE &compare)
        {
            assert(size<capacity);
            assert( Memory::Stealth::Are0(tree+size,sizeof(T)));

            new (tree+size) T(value);
            try
            {
                size_t ipos = Coerce(size)++;
                size_t ppos = heap_parent(ipos);
                while( (ipos>0) && Negative == compare(tree[ppos],tree[ipos]) )
                {
                    Memory::Stealth::Swap(tree[ppos],tree[ipos]);
                    ipos = ppos;
                    ppos = heap_parent(ipos);
                }
            }
            catch(...)
            {
                free();
                throw;
            }
        }

        inline ConstType peek() const noexcept
        {
            assert(size>0);
            assert(0!=tree);
            return tree[0];
        }


        template <typename COMPARE>
        inline Type pop(COMPARE &compare)
        {
            assert(size>0);
            assert(0!=tree);
            try
            {
                MutableType * const target = tree;
                ConstType           result = *target;
                {
                    MutableType * const source =  &tree[--Coerce(size)];
                    Memory::Stealth::Move(target,source,sizeof(T));
                    Memory::Stealth::Zero(source,sizeof(T));
                }
                size_t ipos = 0;
                while(true)
                {
                    const size_t lpos = heap_left(ipos);
                    size_t       mpos = (lpos<size && Negative == compare(target[ipos],target[lpos])) ? lpos : ipos;
                    const size_t rpos = heap_right(ipos);
                    if(rpos<size && Negative == compare(target[mpos],target[rpos]) )
                        mpos = rpos;
                    if(mpos==ipos) break;
                    Memory::Stealth::Swap(target[mpos],target[ipos]);
                    ipos = mpos;
                }
                return result;
            }
            catch(...)
            {
                free();
                throw;
            }
        }


        //! cleanup with zeroed memory
        inline void free() noexcept
        {
            while(size>0)
                Memory::Stealth::DestructedAndZeroed( &tree[--Coerce(size)] );
        }

        MutableType * const tree;
        const size_t        size;
        const size_t        capacity;

    private:
        Y_Disable_Copy_And_Assign(PrioQ);
    };

}

using namespace Yttrium;

Y_UTEST(ordered_pqueue)
{
    void *       wksp[ 10 ];
    const size_t wlen = sizeof(wksp);
    const size_t numBlocks = wlen / sizeof(int);

    PrioQ<int> pq(Memory::Stealth::Cast<int>(Y_Memory_BZero(wksp)), numBlocks);

    pq.push(2, Sign::Decreasing<int> ); std::cerr << pq << std::endl;
    pq.push(7, Sign::Decreasing<int> ); std::cerr << pq << std::endl;
    pq.push(1, Sign::Decreasing<int> ); std::cerr << pq << std::endl;

    Vector<int> vec;
    while(pq.size) vec << pq.pop( Sign::Decreasing<int> );
    std::cerr << vec << std::endl;



}
Y_UDONE()
