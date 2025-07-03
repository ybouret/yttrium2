
//! \file

#ifndef Y_Container_Contiguous_Included
#define Y_Container_Contiguous_Included 1

#include "y/container/writable.hpp"
#include "y/container/iter/linear.hpp"
#include "y/type/conversion.hpp"
#include "y/type/alternative.hpp"
#include "y/check/static.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! user CONTAINER to extract info
    /**
     CONTAINER should be Readable|Writable
     */
    //__________________________________________________________________________
    template <typename CONTAINER>
    class ContiguousCommon : public CONTAINER
    {
    protected:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef typename CONTAINER::Type      Type;      //!< alias
        typedef typename CONTAINER::ConstType ConstType; //!< alias

        using CONTAINER::size;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline explicit ContiguousCommon() noexcept : CONTAINER() {} //!< setup

    public:
        inline virtual ~ContiguousCommon() noexcept {} //!< cleanup


    private:
        Y_Disable_Copy_And_Assign(ContiguousCommon); //!< discarding

    protected:
        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! \return first valid address, may be NULL
        inline ConstType * head() const noexcept {
            const Readable<Type> &self = *this;
            return (size()>0) ? & self[1] : 0;
        }

        //! \return first invalid address, may be NULL
        inline ConstType * last() const noexcept {
            const Readable<Type> &self = *this;
            const size_t       sz   = self.size();
            return  (sz>0) ? & self[1]+sz : 0;
        }

        //! \return first invalid reverse address, may be NULL
        inline ConstType * fore() const noexcept {
            const Readable<Type> &self = *this;
            return (size()>0) ? (&self[1])-1 : 0;
        }


        //! \return first valid revers address, may be NULL
        inline ConstType * tail() const noexcept {
            const Readable<Type> &self = *this;
            const size_t       sz   = self.size();
            return (sz>0) ? (&self[sz]) : 0;
        }

    };

    //__________________________________________________________________________
    //
    //
    //
    //! Decorate CONTAINER  as Readable<Type>
    //
    //
    //__________________________________________________________________________
    template <typename CONTAINER>
    class ReadableContiguous : public ContiguousCommon<CONTAINER>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef typename CONTAINER::Type                 Type;                 //!< alias
        typedef typename CONTAINER::ConstType            ConstType;            //!< alias
        typedef Iter::Linear<Iter::Forward,ConstType>    ConstIterator;        //!< alias
        typedef Iter::Linear<Iter::Reverse,ConstType>    ConstReverseIterator; //!< alias
        using ContiguousCommon<CONTAINER>::head;
        using ContiguousCommon<CONTAINER>::last;
        using ContiguousCommon<CONTAINER>::tail;
        using ContiguousCommon<CONTAINER>::fore;

    protected:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! initialize
        explicit ReadableContiguous() noexcept : ContiguousCommon<CONTAINER>() {
            Y_STATIC_CHECK(Y_Is_SuperSubClass(Readable<Type>,CONTAINER),BadBaseClass);
        }

    public:
        //! cleanup
        virtual ~ReadableContiguous() noexcept {}

        //! \return CONST base address, may be null
        inline ConstType * operator()(void) const noexcept { return head(); }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        inline ConstIterator begin() const noexcept { return head(); } //!< \return first valid ConstIterator
        inline ConstIterator end()   const noexcept { return last(); } //!< \return first invalid ConstIterator

        inline ConstReverseIterator rbegin() const noexcept { return tail(); } //!< \return first valid ConstReverseIterator
        inline ConstReverseIterator rend()   const noexcept { return fore(); } //!< \return first invalid ConstReverseIterator

    private:
        Y_Disable_Copy_And_Assign(ReadableContiguous); //!< discarding
    };

    //__________________________________________________________________________
    //
    //
    //
    //! Decorate CONTAINER<T> as Writable<T>
    //
    //
    //__________________________________________________________________________
    template <typename CONTAINER>
    class WritableContiguous : public ContiguousCommon<CONTAINER>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef typename CONTAINER::Type         Type;                 //!< alias
        typedef typename CONTAINER::MutableType  MutableType;          //!< alias
        typedef typename CONTAINER::ConstType    ConstType;            //!< alias
        using ContiguousCommon<CONTAINER>::head;
        using ContiguousCommon<CONTAINER>::last;
        using ContiguousCommon<CONTAINER>::tail;
        using ContiguousCommon<CONTAINER>::fore;

        typedef Iter::Linear<Iter::Forward,Type>      Iterator;             //!< alias
        typedef Iter::Linear<Iter::Reverse,Type>      ReverseIterator;      //!< alias
        typedef Iter::Linear<Iter::Forward,ConstType> ConstIterator;        //!< alias
        typedef Iter::Linear<Iter::Reverse,ConstType> ConstReverseIterator; //!< alias

    protected:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup
        explicit WritableContiguous() noexcept : ContiguousCommon<CONTAINER>() {
            Y_STATIC_CHECK(Y_Is_SuperSubClass(Writable<Type>,CONTAINER),BadBaseClass);
        }

    public:
        //! cleanup
        virtual ~WritableContiguous() noexcept {}

        //! \return CONST base address, may be null
        inline ConstType * operator()(void) const noexcept { return head(); }

        //! \return base address, may be null
        inline Type *      operator()(void)       noexcept { return (Type*)head(); }


        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        inline Iterator      begin()       noexcept { return (MutableType *)head(); } //!< \return first valid   Iterator
        inline Iterator      end()         noexcept { return (MutableType *)last(); } //!< \return first invalid Iterator

        inline ReverseIterator rbegin()       noexcept { return (MutableType *)tail(); } //!< \return first valid   ReverseIterator
        inline ReverseIterator rend()         noexcept { return (MutableType *)fore(); } //!< \return first invalid ReverseIterator

        inline ConstIterator begin() const noexcept { return head(); } //!< \return first valid   ConstIterator
        inline ConstIterator end()   const noexcept { return last(); } //!< \return first invalid ConstIterator


        inline ConstReverseIterator rbegin() const noexcept { return tail(); } //!< \return first valid   ConstReverseIterator
        inline ConstReverseIterator rend()   const noexcept { return fore(); } //!< \return first invalid ConstReverseIterator


    private:
        Y_Disable_Copy_And_Assign(WritableContiguous); //!< discarding
    };

    //! helper to choose base class for Contiguous
#define Y_Contiguous_Class   Alternative <           \
/**/  Y_Is_SuperSubClass(Writable<typename CONTAINER::Type>,CONTAINER),  \
/**/    WritableContiguous<CONTAINER>,             \
/**/ Y_Is_SuperSubClass(Readable<typename CONTAINER::Type>,CONTAINER),   \
/**/   ReadableContiguous<CONTAINER>,              \
/**/   NullType>::Type

    //__________________________________________________________________________
    //
    //
    //
    //! provide [Const]Iterators to Readable/Writable
    //
    //
    //__________________________________________________________________________
    template <typename CONTAINER>
    class Contiguous : public Y_Contiguous_Class
    {
    protected:
        typedef typename Y_Contiguous_Class ContainerType; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup
        explicit Contiguous() noexcept : ContainerType() {}

    public:
        //! cleanup
        virtual ~Contiguous() noexcept {}

    private:
        Y_Disable_Copy_And_Assign(Contiguous); //!< discarding
    };

}


#endif
