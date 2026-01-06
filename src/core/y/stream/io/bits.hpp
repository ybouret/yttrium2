

//! \file

#ifndef Y_IO_Bits_Included
#define Y_IO_Bits_Included 1

#include "y/stream/io/bit.hpp"
#include "y/protean/proto/list.hpp"
#include "y/container.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/ability/recyclable.hpp"

namespace Yttrium
{
    namespace IO
    {

        //______________________________________________________________________
        //
        //
        //! prototype
        //
        //______________________________________________________________________
        typedef Protean::ListProto<Bit,Bit::Cache &,Container,MultiThreadedObject> BitsProto;


        //______________________________________________________________________
        //
        //
        //
        //! List of IOBits with unique shared cache
        //
        //
        //______________________________________________________________________
        class Bits : public BitsProto, public Recyclable
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //______________________________________________________________________
            explicit Bits();                   //!< setup
            virtual ~Bits() noexcept;          //!< cleanup
            Bits(const Bits & );             //!< duplicate
            Bits & operator=(const Bits & ); //!< assign \return *this
            Y_OSTREAM_PROTO(Bits);



            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void free() noexcept; //!< free content

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void to(Bits &pool) noexcept;


            template <typename T> inline
            Bits & push(T word, size_t nbit, Bits &pool)
            {
                assert(nbit>0); assert(nbit<=sizeof(T)*8);
                static const T one  = 0x1;
                Bits &         self = *this;
                while(nbit-- > 0) {
                    const bool flag = (one&word);
                    if(pool->size)
                        **(self->pushTail( pool->popTail() )) = flag;
                    else
                        self << flag;
                    word >>= 1;
                }
                return  self;
            }

            template <typename T> inline
            Bits & push(const T word, Bits &pool) { return push(word,sizeof(T)*8,pool); }

            template <typename T> inline
            T pop(const size_t nbit, Bits &pool) noexcept
            {
                static const T one = 0x1;
                assert(nbit>0); assert(nbit<=sizeof(T)*8);
                Bits & self = *this; assert(self->size>=nbit);
                T      res  = 0;
                for(size_t i=0;i<nbit;++i)
                {
                    if( **(pool->pushTail( self->popHead() )) )
                        res |= (one<<i);
                }
                return res;
            }



        };
    }
}


#endif // !Y_IO_Bits_Included

