
//! \file

#ifndef Y_PTR_Included
#define Y_PTR_Included 1

#include "y/ptr/immediate.hpp"
#include "y/ptr/drill-down.hpp"
#include <cassert>

#include <iostream>

namespace Yttrium
{

    namespace Core
    {
        class Ptr
        {
        public:
            static const char * const Nil;
            virtual ~Ptr() noexcept;
            explicit Ptr() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Ptr);
        };

        template <typename T>
        class Pointer : public Ptr
        {
        public:
            Y_ARGS_EXPOSE(T,Type);

            virtual ~Pointer() noexcept { handle = 0; }

        protected:
            explicit Pointer(T * const p)  : handle( (MutableType *)p )
            {
            }
            MutableType *handle;
        private:
            Y_Disable_Copy_And_Assign(Pointer);
        };

        class NoNullPointer
        {
        public:
            explicit NoNullPointer(const void * const) noexcept;
            virtual ~NoNullPointer() noexcept;

        private:
            Y_Disable_Copy_And_Assign(NoNullPointer);
        };

    }

    template <typename T>
    class AcceptingNull
    {
    public:
        Y_ARGS_EXPOSE(T,Type);
        inline virtual ~AcceptingNull() noexcept {}
        inline explicit AcceptingNull(MutableType * &h) noexcept : hook( &h ) {}

        inline bool isValid() const noexcept { assert(0!=hook); return 0 != *hook; }
        inline bool isEmpty() const noexcept { assert(0!=hook); return 0 == *hook; }

    private:
        Y_Disable_Copy_And_Assign(AcceptingNull);
        MutableType **hook;
    };

    template <typename T>
    class RejectingNull : public Core::NoNullPointer
    {
    public:
        Y_ARGS_EXPOSE(T,Type);
        inline virtual ~RejectingNull() noexcept {}
        inline explicit RejectingNull(MutableType * const h) noexcept : Core::NoNullPointer(h) {}

    private:
        Y_Disable_Copy_And_Assign(RejectingNull);
    };



    template <
    typename T,
    template <typename> class HandlePolicy,
    template <typename> class AccessPolicy
    >
    class Ptr : public Core::Pointer<T>, public HandlePolicy<T>, public AccessPolicy<T>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef typename AccessPolicy<T>::ReturnType      ReturnType;      //!< alias
        typedef typename AccessPolicy<T>::ConstReturnType ConstReturnType; //!< alias
        Y_ARGS_EXPOSE(T,Type);                                             //!< aliases
        using Core::Pointer<T>::handle;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        inline explicit Ptr(Type *ptr) noexcept :
        Core::Pointer<T>(ptr),
        HandlePolicy<T>(handle),
        AccessPolicy<T>()
        {
        }

    public:
        inline virtual ~Ptr() noexcept { assert(0==handle); }          //!< cleanup

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________


        inline Type      &     operator*()        noexcept { assert(handle); return *handle; }             //!< dereference
        inline ConstType &     operator*()  const noexcept { assert(handle); return *handle; }             //!< dereference, const
        inline ReturnType      operator->()       noexcept { assert(handle); return this->fetch(handle); } //!< access w.r.t. policy
        inline ConstReturnType operator->() const noexcept { assert(handle); return this->fetch(handle); } //!< access w.r.t. policy, const

        //! forwarding display function
        inline friend std::ostream & operator<<(std::ostream &os, const Ptr &self)
        {
            if(self.handle) os << (*self.handle);
            else            os << Core::Ptr::Nil;
            return os;
        }




    private:
        Y_Disable_Copy_And_Assign(Ptr);
    };

}

#endif

