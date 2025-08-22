//! \file

#ifndef Y_Object_Included
#define Y_Object_Included 1

#include "y/core/setup.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Memory
    {
        class Allocator;
    }

    //__________________________________________________________________________
    //
    //
    //
    //! base class for memory allocation
    //
    //
    //__________________________________________________________________________
    class Object
    {
    public:
        class Factory;
        
        explicit Object() noexcept;
        virtual ~Object() noexcept;


        //______________________________________________________________________
        //
        // single object new/delete
        //______________________________________________________________________

        //! acquire memory for new()
        /**
         \param blockSize POSITIVE block size
         \return allocated memory
         */
        static void * operator new(const size_t blockSize);

        //! release previously acquire memory
        /**
         \param blockAddr block address
         \param blockSize block size
         */
        static void   operator delete(void * const blockAddr, const size_t blockSize) noexcept;

        //______________________________________________________________________
        //
        // multiple objects new[]/delete[]
        //______________________________________________________________________
        //! acquire memory for new[]()
        /**
         \param blockSize POSITIVE block size
         \return allocated memory
         */
        static void * operator new    [](const size_t blockSize);

        //! release previously acquired memory
        /**
         \param blockAddr block address
         \param blockSize block size
         */
        static void   operator delete [](void * const blockAddr, const size_t blockSize) noexcept;

        //______________________________________________________________________
        //
        // placement new()/delete()
        //______________________________________________________________________

        //! placement new()
        /**
         \param blockSize positive block size
         \param blockAddr a valid block address
         \return zeroed blockAddr
         */
        static void *operator new(const size_t blockSize, void * const blockAddr) noexcept;

        //! placement delete
        static void  operator delete(void * const , void * const)                 noexcept; 

        static Memory::Allocator & AllocatorInstance();          //!< \return Object::Factory::Instance()
        static Memory::Allocator & AllocatorLocation() noexcept; //!< \return Object::Factory::Location()

        //! \return zeroed block for sizeof(T)
        template <typename T> static inline
        T * ZAcquire() { return static_cast<T*>( operator new( sizeof(T) ) ); }

        //! release acquire block \param impl block address
        template <typename T> static inline
        void ZRelease(T * const impl) { assert(0!=impl); operator delete(impl,sizeof(T)); }

    private:
        Y_Disable_Copy_And_Assign(Object); //!< discarding
    };

}

#endif
