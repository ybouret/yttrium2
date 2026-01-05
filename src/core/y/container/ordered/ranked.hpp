
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
        tree( workspace )
        {
            assert(Good(workspace,numBlocks));
            assert(Memory::Stealth::Are0(workspace,numBlocks*sizeof(T)));
        }



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

        template <typename COMPARE>
        inline void push(ParamType value, COMPARE &compare)
        {
            assert(size<capacity);
            assert( Memory::Stealth::Are0(tree+size,sizeof(T)));

            MutableType * curr = tree+size;
            new (curr) Type(value);
            ++Coerce(size);
            for(MutableType *prev=curr-1;prev>=tree;--prev,--curr)
            {
                switch( compare(*prev,*curr) )
                {
                    case Positive:
                        Memory::Stealth::Swap(prev,curr,sizeof(T));
                        continue;
                    case __Zero__:
                    case Negative:
                        assert( Sorting::Test::AccordingTo(compare,tree,size) );
                        return;
                }
            }

        }




        //! cleanup with zeroed memory
        inline void free() noexcept
        {
            assert( Good(tree,size) );
            while(size>0)
                Memory::Stealth::DestructedAndZeroed( &tree[--Coerce(size)] );
        }

    protected:
        MutableType * const tree;

    private:
        Y_Disable_Copy_And_Assign(Ranked);

    };

}

#endif // !Y_Ranked_Included
