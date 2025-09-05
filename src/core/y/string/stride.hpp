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
                assert(capacity>=other.size);
                memcpy(base,other.base,(size=other.size)*sizeof(T));
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

            //! assign
            /**
             \param source valid source
             \param length length <= capacity
             */
            inline void assign(const T * const source,
                               const size_t    length) noexcept
            {
                assert( Good(source,length) );
                assert( capacity>=length    );
                assert( isValid()           );

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
                    memset(base+length,0,(size-length)*sizeof(T));
                    size = length;
                    assert(isValid());
                }
            }

            //! pushTail
            /**
             \param source valid source
             \param length size+length <= capacity
             */
            inline void pushTail(const T * const source,
                                 const size_t    length) noexcept
            {
                assert( Good(source,length) );
                assert(isValid());
                assert(capacity>=length+size);
                memmove(base+size,source,length*sizeof(T));
                size += length;
                assert(isValid());
            }

            //! pushHead
            /**
             \param source valid source
             \param length size+length <= capacity
             */
            inline void pushHead(const T * const source,
                                 const size_t    length) noexcept
            {
                assert( Good(source,length) );
                assert(isValid());
                assert(capacity>=length+size);

                memmove(base+length,base, size   * sizeof(T));
                memmove(base,source,      length * sizeof(T));
                size += length;
                assert(isValid());
            }

            //! remove first char
            inline void popHead() noexcept
            {
                assert(isValid());
                assert(size>0);
                for(size_t i=1;i<=size;++i)
                {
                    item[i] = base[i];
                }
                base[--size] = 0;
                assert(isValid());
            }

            //! remove last char
            inline void popTail() noexcept
            {
                assert(isValid());
                assert(size>0);
                item[size--] = 0;
                assert(isValid());
            }

            //! erase content
            inline void erase() noexcept
            {
                assert( isValid() );
                memset(base,0,size*sizeof(T));
                size = 0;
                assert( isValid() );
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

