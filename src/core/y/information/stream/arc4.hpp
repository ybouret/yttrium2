//! \file

#ifndef Y_Information_ARC4_Included
#define Y_Information_ARC4_Included 1

#include "y/information/stream/cipher.hpp"

namespace Yttrium
{
    namespace Information
    {
        //______________________________________________________________________
        //
        //
        //
        //! ARC4 symmetric cipher
        //
        //
        //______________________________________________________________________
        struct ARC4
        {
            class Code;

            //__________________________________________________________________
            //
            //
            //! ARC4 implementation
            //
            //__________________________________________________________________
            class Encoder : public StreamCipher
            {
            public:
                //______________________________________________________________
                //
                // C++
                //______________________________________________________________
                virtual ~Encoder() noexcept;                    //!< cleanup
                explicit Encoder(const void *, const size_t  ); //!< setup with key
                explicit Encoder(const char *);                 //!< setup with text

                //______________________________________________________________
                //
                // Interface
                //______________________________________________________________
                virtual void    restart()                 noexcept; //!< rebuild state
                virtual uint8_t operator()(const uint8_t) noexcept; //!< encode/decode \return byte-wise encoded
                virtual size_t  serialize(OutputStream&)  const;    //!< save internal state \return saved bytes
                
            private:
                Y_Disable_Copy_And_Assign(Encoder); //!< discarding
                Code * const code;                  //!< implementation
            };

            //! Decoder is Encoder
            typedef Encoder Decoder;

        };
    }

}

#endif // !Y_Information_ARC4_Included
