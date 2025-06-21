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
        //! String Inner Data Exposure, low-level
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
                assert(other.isValid());
                (void) memcpy(base,other.base,(size=other.size)*sizeof(T));
                assert(isValid());
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
            inline bool isValid() const noexcept {
                return isValidWith(sizeof(T));
            }

            inline void cpy(const T * const source,
                            const size_t    length) noexcept
            {
                assert( Good(source,length) );
                assert(capacity>=length);
                assert(isValid());

                if(size<=length)
                {
                    // overwrite free space
                    memmove(base,source,(size=length)*sizeof(T));
                    assert(isValid());
                }
                else
                {
                    // other is shorter
                    assert(length<size);
                    memmove(base,source,length*sizeof(T));
                    memset(base+length,0,(length-size)*sizeof(T));
                    size = length;
                    assert(isValid());
                }
            }

            inline void cat(const T * const source,
                            const size_t    length) noexcept
            {
                assert( Good(source,length) );
                assert(isValid());
                assert(capacity>=length+size);
                memmove(base+size,source,length*sizeof(T));
                size += length;
                assert(isValid());
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

