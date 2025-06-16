
//! \file

#ifndef Y_Sequence_Included
#define Y_Sequence_Included 1

#include "y/container.hpp"
#include "y/type/args.hpp"
namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Sequence Interface to expand CONTAINER ([Gradual|Dynamic]Container)
    //
    //
    //__________________________________________________________________________
    template <typename T, typename CONTAINER>
    class Sequence : public CONTAINER
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_ARGS_DECL(T,Type); //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        //! setup
        inline explicit Sequence() noexcept : CONTAINER() {}

    public:
        //! cleanup
        inline virtual ~Sequence() noexcept {}

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void pushTail(ParamType) = 0; //!< push object at head of container
        virtual void pushHead(ParamType) = 0; //!< push object at tail of container
        virtual void popTail() noexcept  = 0; //!< pop tail object
        virtual void popHead() noexcept  = 0; //!< pop head object

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! adjust using [pop|push]Tail
        /**
         \param newSize new size to reach
         \param padding default value
        */
        inline void adjust(size_t newSize, ParamType padding)
        {
            const size_t oldSize = this->size();
            while(newSize>oldSize) popTail();
            while(newSize<oldSize) pushTail(padding);
        }

        //! syntactic helper \param rhs value to append \return *this
        Sequence & operator<<(ParamType rhs) { pushTail(rhs); return *this; }

        //! syntactic helper \param lhs value to prepend \return *this
        Sequence& operator>>(ParamType lhs) { pushHead(lhs); return *this; }

    private:
        Y_Disable_Copy_And_Assign(Sequence); //!< discarding
    };

}

#endif
