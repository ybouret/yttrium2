
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
    //! user CONTAINER<T> to extract info
    /**
     CONTAINER should be Readable|Writable
     */
    //__________________________________________________________________________
    template <template <typename> class CONTAINER, typename T>
    class ContiguousCommon : public CONTAINER<T>
    {
    protected:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef typename CONTAINER<T>::ConstType ConstType; //!< alias
        using CONTAINER<T>::size;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline explicit ContiguousCommon() noexcept : CONTAINER<T>() {} //!< setup

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
            const Readable<T> &self = *this;
            return (size()>0) ? & self[1] : 0;
        }

        //! \return first invalid address, may be NULL
        inline ConstType * last() const noexcept {
            const Readable<T> &self = *this;
            const size_t       sz   = self.size();
            return  (sz>0) ? & self[1]+sz : 0;
        }
    };

    //__________________________________________________________________________
    //
    //
    //
    //! Decorate CONTAINER<T> as Readable<T>
    //
    //
    //__________________________________________________________________________
    template <template <typename> class CONTAINER, typename T>
    class ReadableContiguous : public ContiguousCommon<CONTAINER,T>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_ARGS_EXPOSE(T,Type); //!< aliases
        typedef Iter::Linear<Iter::Forward,ConstType> ConstIterator; //!< alias

    protected:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! initialize
        explicit ReadableContiguous() noexcept : ContiguousCommon<CONTAINER,T>() {
            Y_STATIC_CHECK(Y_Is_SuperSubClass(Readable<T>,CONTAINER<T>),BadBaseClass);
        }

    public:
        //! cleanup
        virtual ~ReadableContiguous() noexcept {}

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        inline ConstIterator begin() const noexcept { return this->head(); } //!< \return first valid ConstIterator
        inline ConstIterator end()   const noexcept { return this->last(); } //!< \return first invalid ConstIterator

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
    template <template <typename> class CONTAINER, typename T>
    class WritableContiguous : public ContiguousCommon<CONTAINER,T>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        using ContiguousCommon<CONTAINER,T>::head;
        using ContiguousCommon<CONTAINER,T>::last;

        Y_ARGS_EXPOSE(T,Type);                                       //!< aliases
        typedef Iter::Linear<Iter::Forward,ConstType> ConstIterator; //!< alias
        typedef Iter::Linear<Iter::Forward,ConstType> Iterator;      //!< alias

    protected:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup
        explicit WritableContiguous() noexcept : ContiguousCommon<CONTAINER,T>() {
            Y_STATIC_CHECK(Y_Is_SuperSubClass(Writable<T>,CONTAINER<T>),BadBaseClass);
        }

    public:
        //! cleanup
        virtual ~WritableContiguous() noexcept {}

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        inline ConstIterator begin() const noexcept { return head(); } //!< \return first valid  ConstIterator
        inline ConstIterator end()   const noexcept { return last(); } //!< \return first invalid ConstIterator
        inline Iterator      begin()       noexcept { return head(); } //!< \return first valid   Iterator
        inline Iterator      end()         noexcept { return last(); } //!< \return first invalid Iterator

    private:
        Y_Disable_Copy_And_Assign(WritableContiguous); //!< discarding
    };

    //! helper to choose base class for Contiguous
#define Y_Contiguous_Class   Alternative <           \
/**/  Y_Is_SuperSubClass(Writable<T>,CONTAINER<T>),  \
/**/    WritableContiguous<CONTAINER,T>,             \
/**/ Y_Is_SuperSubClass(Readable<T>,CONTAINER<T>),   \
/**/   ReadableContiguous<CONTAINER,T>,              \
/**/   NullType>::Type

    //__________________________________________________________________________
    //
    //
    //
    //! provide [Const]Iterators to Readable/Writable
    //
    //
    //__________________________________________________________________________
    template <template <typename> class CONTAINER, typename T>
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
