
//! \file

#ifndef Y_Information_Verbatim_Included
#define Y_Information_Verbatim_Included 1

#include "y/information/stream/cipher.hpp"

namespace Yttrium
{
    namespace Information
    {
        //______________________________________________________________________
        //
        //
        //
        //! Verbatim
        //
        //
        //______________________________________________________________________
        struct Verbatim
        {

            //__________________________________________________________________
            //
            //
            //! Encoder
            //
            //__________________________________________________________________
            class Encoder : public StreamCipher
            {
            public:
                explicit Encoder() noexcept; //!< setup
                virtual ~Encoder() noexcept; //!< cleanup

                virtual size_t  serialize(OutputStream&)   const;
                virtual void    restart()                  noexcept;
                virtual uint8_t operator()(const uint8_t ) noexcept;
                
            private:
                Y_Disable_Copy_And_Assign(Encoder); //!< discarding
            };

            //__________________________________________________________________
            //
            //
            //! Decoder
            //
            //__________________________________________________________________
            typedef Encoder Decoder;

        };

    }

}

#endif // !Y_Information_Verbatim_Included
