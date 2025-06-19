//!\ file


#ifndef Y_String_Stride_Included
#define Y_String_Stride_Included 1

#include "y/string/stride/metrics.hpp"
#include <cstring>
#include <cassert>

namespace Yttrium
{
    namespace Core
    {

       
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

            //! duplicate content \param other another stride
            inline Stride(const Stride &other) :
            StrideMetrics(other.size,sizeof(T)),
            base( static_cast<T *>(address) ),
            item(base-1)
            {
                assert(other.checked());
                (void) memcpy(base,other.base,(size=other.size)*sizeof(T));
                assert(checked());
            }

            //! cleanup
            inline virtual ~Stride() noexcept
            {
                Coerce(base) = Coerce(item) = 0;
            }


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return checked state, mostly for debug
            inline bool checked() const noexcept
            {
                return sanity(sizeof(T));
            }


            //!
            inline void copy(const Stride<T> &other) noexcept
            {
                assert(this!=&other);
                assert(capacity>=other.size);
                assert( checked() );
                assert( other.checked() );

                const size_t newSize = other.size;
                if(size<=newSize)
                {
                    // overwrite free space
                    memcpy(base,other.base,(size=newSize)*sizeof(T));
                    assert(checked());
                }
                else
                {
                    // other is shorter
                    assert(newSize<size);
                    memcpy(base,other.base,newSize*sizeof(T));
                    memset(base+newSize,0,(newSize-size)*sizeof(T));
                    size = newSize;
                    assert(checked());
                }
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
            Y_Disable_Assign(Stride); //!< discarding
            
        };
        
    }
}

#endif

