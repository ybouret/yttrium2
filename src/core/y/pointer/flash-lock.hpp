
//! \file

#ifndef Y_Pointer_FlashLock_Included
#define Y_Pointer_FlashLock_Included 1

#include "y/type/args.hpp"
#include <cassert>

namespace Yttrium
{

    namespace Smart
    {
        //______________________________________________________________________
        //
        //
        //
        //! helper for operator->
        //
        //
        //______________________________________________________________________
        template <class T> class LockingProxy
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Expose(T,Type); //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! initialize \param ptr object that shall be locked
            inline LockingProxy(T * const ptr) : pointee((MutableType*)ptr)
            {
                assert(0!=pointee);
                pointee->lock();
            }

            //! cleanup, unlock object
            inline ~LockingProxy() noexcept {
                assert(0!=pointee);
                pointee->unlock();
            }

            //! \return locked object address
            inline Type * operator->() noexcept {
                assert(0!=pointee);
                return pointee;
            }

            //! duplicate \param other
            inline LockingProxy(const LockingProxy &other) noexcept :
            pointee(other.pointee)
            {
            }

        private:
            Y_Disable_Assign(LockingProxy); //!< discarding
            MutableType * const pointee;    //!< object address
        };
    }

    //__________________________________________________________________________
    //
    //
    //
    //! return a temporary locked proxy
    //
    //
    //__________________________________________________________________________
    template <class T> class FlashLock
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Expose(T,Type);                                  //!< aliases
        typedef Smart::LockingProxy<Type>      ReturnType;      //!< alias
        typedef Smart::LockingProxy<ConstType> ConstReturnType; //!< alias


        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline virtual ~FlashLock() noexcept {} //!< cleanup
    protected:
        inline explicit FlashLock() noexcept {} //!< setup

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! \return locking proxy \param ptr object to lock
        inline ReturnType      fetch(Type      * const ptr)       noexcept { assert(0!=ptr); return ReturnType(ptr); }

        //! \return CONST locking proxy \param ptr object to lock
        inline ConstReturnType fetch(ConstType * const ptr) const noexcept { assert(0!=ptr); return ConstReturnType(ptr); }

    private:
        Y_Disable_Copy_And_Assign(FlashLock); //!< discarding
    };


}

#endif
