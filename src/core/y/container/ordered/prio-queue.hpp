
//! \file

#ifndef Y_PrioQ_Included
#define Y_PrioQ_Included 1


#include "y/container/ordered/pqueue.hpp"
#include "y/type/args.hpp"
#include "y/memory/stealth.hpp"
#include "y/type/destruct.hpp"
#include "y/check/usual.hpp"
#include "y/core/display.hpp"
#include "y/type/sign.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Managing objects in given memory with given comparison
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class PrioQueue : public PQueue
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

        //! setup from user's memory
        /**
         \param workspace zeroed memory space
         \param numBlocks maximum objects to handle
         */
        inline explicit PrioQueue(T * const    workspace,
                                  const size_t numBlocks) noexcept :
        PQueue(numBlocks),
        tree( workspace )
        {
            assert(Good(workspace,numBlocks));
            assert(Memory::Stealth::Are0(workspace,numBlocks*sizeof(T)));
        }

        //! cleanup
        virtual ~PrioQueue() noexcept
        {
            assert(Good(tree,size));
            free();
            Coerce(tree)     = 0;
            Coerce(capacity) = 0;
        }

        //! print internal state
        /**
         \param os output stream
         \param self *this
         \return output stream
         */
        inline friend std::ostream & operator<<(std::ostream &os, const PrioQueue &self)
        {
            return Core::Display(os,self.tree,self.size);
        }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! steal content \param q stolen queue
        inline void steal(PrioQueue &q) noexcept
        {
            assert(this != &q);
            assert(0    == size);
            assert(capacity>=q.size);
            
            Memory::Stealth::SafeCopy(tree,q.tree, (Coerce(size) = q.size)*sizeof(T) );
            Coerce(q.size) = 0;
        }

        //! append value and restore state
        /**
         \param value value to insert
         \param compare SignType compare(lhs,rhs)
         */
        template <typename COMPARE>
        inline void push(ParamType value, COMPARE &compare)
        {
            assert(size<capacity);
            assert( Memory::Stealth::Are0(tree+size,sizeof(T)));

            new (tree+size) T(value);
            balance(compare);
        }

        //! balance and update size after push \param compare comparison function
        template <typename COMPARE> inline
        void balance(COMPARE &compare)
        {
            try
            {
                size_t ipos = Coerce(size)++;
                size_t ppos = Parent(ipos);
                while( (ipos>0) && Negative == compare(tree[ppos],tree[ipos]) )
                {
                    Memory::Stealth::Swap(tree[ppos],tree[ipos]);
                    ipos = ppos;
                    ppos = Parent(ipos);
                }
            }
            catch(...)
            {
                free();
                throw;
            }
        }
        


        //! \return top object
        inline ConstType peek() const noexcept
        {
            assert(size>0);
            assert(0!=tree);
            return tree[0];
        }

        //! return and remove top object
        /**
         \param compare SignType compare(lhs,rhs)
         \return top content
         */
        template <typename COMPARE>
        inline Type pop(COMPARE &compare)
        {
            assert(size>0);
            assert(0!=tree);
            try
            {
                MutableType * const target = tree;
                ConstType           result = *target;
                Destruct(target);
                {
                    MutableType * const source =  &tree[--Coerce(size)];
                    Memory::Stealth::Move(target,source,sizeof(T));
                    Memory::Stealth::Zero(source,sizeof(T));
                }
                size_t ipos = 0;
                while(true)
                {
                    size_t mpos = ipos;
                    {
                        size_t tpos = ipos << 1;
                        ++tpos; if((tpos<size && Negative == compare(target[ipos],target[tpos])) ) mpos = tpos;
                        ++tpos; if((tpos<size && Negative == compare(target[mpos],target[tpos])) ) mpos = tpos;
                    }
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

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        MutableType * const tree; //!< internal tree

    private:
        Y_Disable_Copy_And_Assign(PrioQueue); //!< discarding
    };

}

#endif

