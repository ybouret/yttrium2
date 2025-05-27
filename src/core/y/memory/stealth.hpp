//! \file

#ifndef Y_Memory_Stealth_Included
#define Y_Memory_Stealth_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! aliasing-free memory operations
        //
        //
        //______________________________________________________________________
        struct Stealth
        {

            //! alias address
            /**
             \param address any address
             \return out-of-reach address
             */
            static void *       Address(void * const       address) noexcept;

            //! alias const address
            /**
             \param address any address
             \return out-of-reach address
             */
            static const void * Address(const void * const address) noexcept;

            //! zero memory block
            /**
             \param blockAddr address
             \param blockSize bytes to zero
             \return zeroed blockAddr
             */
            static void *       Zero(void * const blockAddr,
                                     const size_t blockSize) noexcept;

            //! check zeroed block
            /**
             \param blockAddr address
             \param blockSize bytes to check
             \return true if all bytes are 0
             */
            static bool         Are0(const void * const blockAddr,
                                     const size_t       blockSize) noexcept;

            static void *       Copy(void * const       target,
                                     const void * const source,
                                     const size_t       bytes) noexcept;
            
            //! memory swap
            /**
             \param lhsBlock lhs address
             \param rhsBlock rhs address
             \param blockSize common block size
             */
            static void         Swap(void * const lhsBlock,
                                     void * const rhsBlock,
                                     const size_t blockSize) noexcept;

            //! alias and cast
            /** \param address \return casted address */
            template <typename T>
            static inline T *Cast(void * const address) noexcept
            {
                return static_cast<T *>( Address(address) );
            }

            //! alias and const cast
            /** \param address \return casted address */
            template <typename T>
            static inline const T *Cast(const void * const address) noexcept
            {
                return static_cast<const T *>( Address(address) );
            }

            //! alias and cast a zeroed block
            /**
             \param address base address
             \return casted address with zeroed bytes
             */
            template <typename T>
            static inline T *CastZeroed(void * const address) noexcept
            {
                return static_cast<T *>(Zero(address,sizeof(T)));
            }
            

        };
    }

    //! helper to zero a local block of memory
#define Y_Memory_BZero(BLOCK) Memory::Stealth::Zero(BLOCK,sizeof(BLOCK))

}

#endif

