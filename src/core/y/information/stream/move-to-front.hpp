
//! \file

#ifndef Y_Information_Move_To_Front_Included
#define Y_Information_Move_To_Front_Included 1

#include "y/information/stream/cipher.hpp"

namespace Yttrium
{
    namespace Information
    {
        //______________________________________________________________________
        //
        //
        //
        //! Move To Front Encoding/Decoding
        //
        //
        //______________________________________________________________________
        struct MoveToFront
        {
            class Code;

            //__________________________________________________________________
            //
            //
            //! Shared components
            //
            //__________________________________________________________________
            class Common : public StreamCipher
            {
            public:
                virtual void   restart() noexcept;
                virtual size_t serialize(OutputStream&) const;

                virtual     ~Common()  noexcept; //!< cleanup
            protected:
                explicit     Common();           //!< setup code
                Code * const code;                   //!< implementation
            private:
                Y_Disable_Copy_And_Assign(Common);
            };

            //__________________________________________________________________
            //
            //
            //! Encoder
            //
            //__________________________________________________________________
            class Encoder : public Common
            {
            public:
                explicit Encoder();
                virtual ~Encoder() noexcept;
                virtual uint8_t operator()(const uint8_t ) noexcept;
            private:
                Y_Disable_Copy_And_Assign(Encoder);
            };

            //__________________________________________________________________
            //
            //
            //! Decoder
            //
            //__________________________________________________________________
            class Decoder : public Common
            {
            public:
                explicit Decoder();
                virtual ~Decoder() noexcept;

                virtual uint8_t operator()(const uint8_t ) noexcept;

            private:
                Y_Disable_Copy_And_Assign(Decoder);
            };
        };

    }

}

#endif
