
//! \file

#ifndef Y_Ranked_Included
#define Y_Ranked_Included 1


#include "y/container/ordered/queue.hpp"
#include "y/check/usual.hpp"
#include "y/memory/stealth.hpp"
#include "y/type/args.hpp"
#include "y/core/display.hpp"
#include "y/type/sign.hpp"
#include "y/sorting/test.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! base class for linear queues
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class Ranked : public Queue
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
        inline explicit Ranked(MutableType * const workspace,
                               const size_t        numBlocks) noexcept :
        Queue(numBlocks),
        tree( workspace ),
        most(0)
        {
            assert(Good(workspace,numBlocks));
            assert(Memory::Stealth::Are0(workspace,numBlocks*sizeof(T)));
        }


        //! cleanup
        inline virtual ~Ranked() noexcept
        {
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
        inline friend std::ostream & operator<<(std::ostream &os, const Ranked &self)
        {
            return Core::Display(os,self.tree,self.size);
        }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! push a new item \param value new value \param compare comparison
        template <typename COMPARE>
        inline void push(ParamType value, COMPARE & compare)
        {
            assert(size<capacity);
            assert( Memory::Stealth::Are0(tree+size,sizeof(T)));

            // append new type
            MutableType * curr = tree+size;
            new (curr) Type(value);

            // update structure
            Coerce(most) = curr;
            ++Coerce(size);

            try
            {
                // in place sorting
                for(MutableType *prev=curr-1;prev>=tree;--prev,--curr)
                {
                    switch( compare(*prev,*curr) )
                    {
                        case Positive:
                            Memory::Stealth::Swap(prev,curr,sizeof(T));
                            continue;
                        case __Zero__:
                        case Negative:
                            assert( sanity(compare) );
                            return;
                    }
                }
            }
            catch(...)
            {
                free();
                throw;
            }
        }


        //! \return top object reference
        inline ConstType &peek() const noexcept
        {
            assert(size>0);
            assert(0!=tree);
            assert(tree+size==most+1);
            return *most;
        }

        //! \return copy of removed top object
        inline Type pop()
        {
            assert(size>0);
            assert(0!=tree);
            assert(tree+size==most+1);
            ConstType result = *most;
            (void) Memory::Stealth::DestructedAndZeroed(most);
            if( --Coerce(size) <= 0 ) Coerce(most) = 0; else --Coerce(most);
            return result;
        }


        //! cleanup with zeroed memory
        inline void free() noexcept
        {
            assert( Good(tree,size) );
            while(size>0)
                Memory::Stealth::DestructedAndZeroed( &tree[--Coerce(size)] );
            Coerce(most) = 0;
        }

        //! steal content \param from another
        inline void steal(Ranked &from) noexcept
        {
            assert(0==size); assert(0==most);
            assert(capacity>=from.size);
            Memory::Stealth::Copy(tree,from.tree, (Coerce(size)=from.size) * sizeof(T));
            most = tree + size;
            Coerce(from.size) = 0;
            --Coerce(most);
            from.most = 0;
        }



        //! update \param curr changed value \param compare comparison
        template <typename COMPARE>
        bool updated(MutableType * const curr, COMPARE &compare)
        {
            assert(curr>=tree);
            assert(curr<=most);
            try
            {
                if( updatedByPrev(curr,compare) ) return true;
                if( updatedByNext(curr,compare) ) return true;
                assert( sanity(compare) );
            }
            catch(...)
            {
                free();
                throw;
            }
            return false;

        }

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        MutableType * const tree; //!< head item
        MutableType * const most; //!< tail item (0 if size==0)

    private:
        Y_Disable_Copy_And_Assign(Ranked); //!< discarding

        //! mostly to debug \param compare comparison \return sanity check
        template <typename COMPARE>
        inline bool sanity(COMPARE &compare) const noexcept {
            return Sorting::Test::AccordingTo(compare,tree,size) ;
        }

        template <typename COMPARE> inline
        bool updatedByPrev(MutableType *curr, COMPARE &compare)
        {
            bool moved = false;
            for(MutableType *prev=curr-1;prev>=tree;--prev,--curr)
            {
                switch( compare(*prev,*curr) )
                {
                    case Positive:
                        Memory::Stealth::Swap(prev,curr,sizeof(T));
                        moved = true;
                        continue;

                    case __Zero__:
                    case Negative:
                        goto DONE;
                }
            }

        DONE:
            return moved;
        }

        template <typename COMPARE> inline
        bool updatedByNext(MutableType *curr, COMPARE &compare)
        {
            bool moved = false;
            for(MutableType *next=curr+1;next<=most;++next,++curr)
            {
                switch( compare(*curr,*next) )
                {
                    case Positive:
                        Memory::Stealth::Swap(next,curr,sizeof(T));
                        moved = true;
                        continue;

                    case __Zero__:
                    case Negative:
                        goto DONE;
                }
            }
        DONE:
            return moved;
        }


    };

}

#endif // !Y_Ranked_Included
