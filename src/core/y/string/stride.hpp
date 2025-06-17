//!\ file


#ifndef Y_String_Stride_Included
#define Y_String_Stride_Included 1

#include "y/object.hpp"
namespace Yttrium
{

    namespace Core
    {
        class StrideMetrics : public Object
        {
        protected:
            explicit StrideMetrics(const size_t minimalCapacity,
                                   const size_t bytesPerChar) noexcept;

        public:
            virtual ~StrideMetrics() noexcept;


            size_t       size;
            const size_t capacity;

        protected:
            void * const address;

        private:
            Y_Disable_Copy_And_Assign(StrideMetrics);
            const size_t numChars;
            const size_t obtained;
        };

        template <typename T>
        class Stride : public StrideMetrics
        {
        public:
            inline explicit Stride(const size_t minimalCapacity) :
            StrideMetrics(minimalCapacity,sizeof(T)),
            base( static_cast<T *>(address) ),
            item(base-1)
            {
            }

            inline virtual ~Stride() noexcept
            {
                Coerce(base) = Coerce(item) = 0;
            }

            T * const base;
            T * const item;

        private:
            Y_Disable_Copy_And_Assign(Stride);
        };
    }

}

#endif

