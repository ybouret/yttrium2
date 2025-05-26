
//! \file

#ifndef Y_System_Rand_Included
#define Y_System_Rand_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace System
    {

        //______________________________________________________________________
        //
        //
        //
        //! rand() wrapper
        //
        //
        //______________________________________________________________________
        class Rand
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //
            //__________________________________________________________________
            explicit Rand() noexcept;
            virtual ~Rand() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            //! convert to [float|double|long double]
            /** \return "]0:1[" */
            template <typename T> T to() noexcept;

            //! uniform [0:n]
            /** \param n any integer \return [0:n] */
            size_t leq(const size_t n) noexcept;

            //! uniform [1..n]
            /** \param n>0 \return [1:n] */
            size_t in(const size_t n) noexcept;


            //! half probability
            /** \return true with proba=0.5 */
            bool choice() noexcept;

            //! Knuth shuffle
            /**
             \param blockAddr base address
             \param numBlocks number of items
             \param blockSize size of each item
             */
            void shuffle(void * const blockAddr,
                         const size_t numBlocks,
                         const size_t blockSize) noexcept;

            //! Knuth shuffle wrapper
            /**
             \param blockAddr address of tableau
             \param numBlocks itens in tableau
             */
            template <typename T> inline
            void shuffle( T * const blockAddr, const size_t numBlocks) noexcept
            {
                shuffle(blockAddr,numBlocks,sizeof(T));
            }

            //! fill with garbage
            /**
             \param blockAddr base address
             \param blockSize bytes to fill
             */
            void fill(void * const blockAddr, const size_t blockSize) noexcept;

        private:
            Y_Disable_Copy_And_Assign(Rand); //!< discarding
        };

    }
}

#endif

