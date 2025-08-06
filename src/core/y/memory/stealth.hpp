//! \file

#ifndef Y_Memory_Stealth_Included
#define Y_Memory_Stealth_Included 1

#include "y/core/setup.hpp"
#include <cassert>

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

            //! copy memory blocks
            /**
             \param target target address
             \param source source address
             \param bytes  bytes to copy
             \return target
             */
            static void *       Copy(void * const       target,
                                     const void * const source,
                                     const size_t       bytes) noexcept;

            //! copy memory blocks and zero source
            /**
             \param target target address
             \param source source address
             \param bytes  bytes to copy
             \return target
             */
            static void *       SafeCopy(void * const target,
                                         void * const source,
                                         const size_t bytes) noexcept;

            //! move memory blocks
            /**
             \param target target address
             \param source source address
             \param bytes  bytes to copy
             \return target
             */
            static void *       Move(void * const       target,
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


            //! memory copy
            /**
             \param lhs first item
             \param rhs second item
             */
            template <typename T> static inline
            void Copy( T &lhs, const T &rhs ) noexcept
            {
                Copy( &lhs, &rhs, sizeof(T) );
            }

            //! memory swap
            /**
             \param lhs first item
             \param rhs second item
             */
            template <typename T> static inline
            void Swap( T &lhs, T &rhs ) noexcept
            {
                Swap( &lhs, &rhs, sizeof(T) );
            }

            //! anonymous memory address increase
            /**
             \param addr
             \param delta
             \return addr plus delta bytes
             */
            static void * Incr(void * const addr,
                               const size_t delta) noexcept;

            //! anonymous memory address decrease
            /**
             \param addr
             \param delta
             \return addr minus delta bytes
             */
            static void * Decr(void * const addr,
                               const size_t delta) noexcept;



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

            //! clean destruction
            /**
             \param  obj a valid object
             \return clean and destructed object
             */
            template <typename T>
            static inline T * DestructedAndZeroed( T * const obj ) noexcept
            {
                assert(0!=obj);
                obj->~T();
                return static_cast<T*>(Zero(obj,sizeof(T)));
            }

            //! anonymous address difference
            /**
             \param ini any address
             \param end any address
             \return end-ini difference in bytes
             */
            static ptrdiff_t Diff(const void * const ini, const void *const end) noexcept;

            //! \return hidden address location \param addr address to hide
            template <typename T> static inline
            T * Hide(T * const addr) noexcept {
                return (T*)Address(addr);
            }

        };
    }

    //! helper to zero a local block of memory
#define Y_Memory_BZero(BLOCK) Memory::Stealth::Zero(BLOCK,sizeof(BLOCK))

    //! helper to zero a local variable
#define Y_Memory_VZero(VAR) Memory::Stealth::Zero(&VAR,sizeof(VAR))


}

#endif

