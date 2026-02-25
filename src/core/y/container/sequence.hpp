
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
    //! Sequence Interface to expand CONTAINER ([Gradual|Dynamic<>]Container...)
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
        Y_Args_Declare(T,Type); //!< aliases

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
        inline void adjust(const size_t newSize, ParamType padding)
        {
            while(this->size()>newSize) popTail();
            while(this->size()<newSize) pushTail(padding);
        }

        //! syntactic helper \param rhs value to append \return *this
        Sequence & operator<<(ParamType rhs) { pushTail(rhs); return *this; }

        //! syntactic helper \param lhs value to prepend \return *this
        Sequence& operator>>(ParamType lhs) { pushHead(lhs); return *this; }


        inline Type      & head()       noexcept { assert(this->size()>0 ); return Coerce(getHead()); } //!< \return head item
        inline Type      & tail()       noexcept { assert(this->size()>0 ); return Coerce(getTail()); } //!< \return tail item
        inline ConstType & head() const noexcept { assert(this->size()>0 ); return getHead(); }         //!< \return head item
        inline ConstType & tail() const noexcept { assert(this->size()>0 ); return getTail(); }         //!< \return tail item

        //! \return tail element, removed
        inline Type pullTail() {
            assert(this->size()>0 );
            Type res = tail(); popTail(); return res;
        }

    private:
        Y_Disable_Copy_And_Assign(Sequence); //!< discarding

        virtual ConstType & getHead()             const noexcept = 0; //!< \return head item
        virtual ConstType & getTail()             const noexcept = 0; //!< \return tail item
        //virtual ConstType & getBulk(const size_t) const noexcept = 0;
    };

}

#endif // !Y_Sequence_Included
