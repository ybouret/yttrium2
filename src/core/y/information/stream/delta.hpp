

//! \file

#ifndef Y_Information_Delta_Included
#define Y_Information_Delta_Included 1

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
        struct Delta
        {

            //__________________________________________________________________
            //
            //
            //! Shared components
            //
            //__________________________________________________________________
            class Common : public StreamCipher
            {
            public:
                //______________________________________________________________
                //
                // Interface
                //______________________________________________________________
                virtual void   restart() noexcept;
                virtual size_t serialize(OutputStream&) const;

                //______________________________________________________________
                //
                // C++
                //______________________________________________________________
                virtual     ~Common()  noexcept; //!< cleanup
            protected:
                explicit     Common();           //!< setup code

                //______________________________________________________________
                //
                // Members
                //______________________________________________________________
                uint8_t      last;               //!< for implementation
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
