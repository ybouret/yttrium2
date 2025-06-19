
//!\ file


#ifndef Y_String_Stride_Metrics_Included
#define Y_String_Stride_Metrics_Included 1

#include "y/object.hpp"

namespace Yttrium
{
    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //
        //! Metrics for Stride
        //
        //
        //______________________________________________________________________
        class StrideMetrics : public Object
        {
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            //! setup memory and parameters
            /**
             \param minimalCapacity capacity >= minimalCapacity
             \param blockSize       sizeof(T)
             */
            explicit StrideMetrics(const size_t minimalCapacity,
                                   const size_t blockSize) noexcept;

        public:
            //! cleanup
            virtual ~StrideMetrics() noexcept;

            //! check current sanity \param blockSize sizeof(T) \return true iff alright
            bool sanity(const size_t blockSize) const noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            size_t       size;     //!< current chars
            const size_t capacity; //!< size <= capacity

        protected:
            void * const address;  //!< allocated memory

        private:
            Y_Disable_Copy_And_Assign(StrideMetrics); //!< discarding
            const size_t numChars; //!< capacity+1
            const size_t obtained; //!< acquired bytes
        };

    }

}

#endif

