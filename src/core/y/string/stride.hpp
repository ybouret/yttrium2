//!\ file


#ifndef Y_String_Stride_Included
#define Y_String_Stride_Included 1

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
             \param bytesPerChar    positive count
             */
            explicit StrideMetrics(const size_t minimalCapacity,
                                   const size_t bytesPerChar) noexcept;

        public:
            //! cleanup
            virtual ~StrideMetrics() noexcept;

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


        //______________________________________________________________________
        //
        //
        //
        //! String Inner Data Exposure
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Stride : public StrideMetrics
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param minimalCapacity required capacity
            inline explicit Stride(const size_t minimalCapacity) :
            StrideMetrics(minimalCapacity,sizeof(T)),
            base( static_cast<T *>(address) ),
            item(base-1)
            {
            }

            //! cleanup
            inline virtual ~Stride() noexcept
            {
                Coerce(base) = Coerce(item) = 0;
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            T * const base; //!< [0..size-1] access
            T * const item; //!< [1..size]   access

        private:
            Y_Disable_Copy_And_Assign(Stride); //!< discarding
        };
    }

}

#endif

