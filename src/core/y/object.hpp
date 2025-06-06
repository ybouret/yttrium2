//! \file

#ifndef Y_Object_Included
#define Y_Object_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{

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
        static void * operator new(const size_t blockSize);                                     //!< new(blockSize)
        static void   operator delete(void * const blockAddr, const size_t blockSize) noexcept; //!< delete(blockSize)

        //______________________________________________________________________
        //
        // multiple objects new[]/delete[]
        //______________________________________________________________________
        static void * operator new    [](const size_t blockSize);                                  //!< new[block_size]
        static void   operator delete [](void * const blockAddr, const size_t blockSize) noexcept; //!< delete[block_size]

        //______________________________________________________________________
        //
        // placement new()/delete()
        //______________________________________________________________________
        static void *operator new(const size_t blockSize, void * const blockAddr) noexcept; //!< placement new
        static void  operator delete(void * const , void * const)                  noexcept; //!< placement delete

    private:
        Y_Disable_Copy_And_Assign(Object);
    };

}

#endif
