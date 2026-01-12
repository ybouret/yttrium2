

//! \file

#ifndef Y_IO_Bits_Included
#define Y_IO_Bits_Included 1

#include "y/stream/io/bit.hpp"
#include "y/protean/proto/list.hpp"
#include "y/container.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/ability/recyclable.hpp"
#include "y/stream/output.hpp"

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
        //! List of IOBits with unique shared cache TODO check locking...
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
            explicit Bits();                 //!< setup
            virtual ~Bits() noexcept;        //!< cleanup
            Bits(const Bits & );             //!< duplicate
            Bits & operator=(const Bits & ); //!< assign \return *this
            Y_OSTREAM_PROTO(Bits);           //!< display



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
            //! drop content into pool
            /**
             \param reservoir reservoir
             \return emptied
             */
            Bits & to(Bits &reservoir)                noexcept;

            //! skip bits
            /**
             \param nbit      bits to skip
             \param reservoir reservoir
             \return skipped
             */
            Bits & skip(size_t nbit, Bits &reservoir) noexcept;

            //! write as many bytes as possible into output
            /**
             \param output    output stream
             \param reservoir reservoir
             \return written bytes
             */
            size_t write(OutputStream &output, Bits &reservoir);


            //! write and emit padded
            /**
             \param output    output stream
             \param reservoir reservoir
             \return written bytes
             */
            size_t flush(OutputStream &output, Bits &reservoir);


            //! push a partial word
            /**
             \param word      word to push
             \param nbit      1<=nbit<=sizeof(word)*8
             \param reservoir pool
             \return *this
             */
            template <typename T> inline
            Bits & push(T word, size_t nbit, Bits &reservoir)
            {
                volatile Lock _(*this), __(reservoir);
                assert(nbit>0); assert(nbit<=sizeof(T)*8);
                static const T one  = 0x1;
                while(nbit-- > 0) {
                    list.pushTail(reservoir.query(one&word));
                    word >>= 1;
                }
                return  *this;
            }

            //! push a  full word
            /**
             \param word      word to push
             \param reservoir reservoir
             \return *this
             */
            template <typename T> inline
            Bits & push(const T word, Bits &reservoir) { return push(word,sizeof(T)*8, reservoir); }

            //! pop a partial word
            /**
             \param nbit      1<=nbit<=sizeof(T)*8
             \param reservoir reservoir
             \return result
             */
            template <typename T> inline
            T pop(const size_t nbit, Bits &reservoir) noexcept
            {
                volatile Lock _(*this), __(reservoir);
                assert(nbit>0);
                assert(nbit<=sizeof(T)*8);
                assert(list.size>=nbit);

                static const T one = 0x1;
                T              res = 0;
                for(size_t i=0;i<nbit;++i)
                {
                    if( **(reservoir->pushTail( list.popHead() )) )
                        res |= (one<<i);
                }
                return res;
            }

            //! pop a full word
            /**
             \param reservoir reservoir
             \return result
             */
            template <typename T> inline
            T pop(Bits &reservoir) noexcept {
                return pop<T>( sizeof(T) * 8, reservoir);
            }


            //! peek a partial word
            /**
             \param nbit 1<=nbit<=sizeof(T)*8
             \return result
             */
            template <typename T> inline
            T peek(const size_t nbit) const noexcept
            {
                assert(nbit>0);
                assert(nbit<=sizeof(T)*8);
                assert(list.size>=nbit);
                static const T one = 0x1;
                T              res = 0;
                const Bit     *bit = list.head;
                for(size_t i=0;i<nbit;++i,bit=bit->next)
                {
                    assert(bit);
                    if(**bit)
                        res |= (one<<i);
                }
                return res;
            }

            //! \return full word
            template <typename T> inline
            T peek() const noexcept
            {
                return peek<T>( sizeof(T) * 8 );
            }



        };
    }
}


#endif // !Y_IO_Bits_Included

