//! \file

#ifndef Y_Information_Stream_Cipher_Included
#define Y_Information_Stream_Cipher_Included 1

#include "y/ability/serializable.hpp"

namespace Yttrium
{
    namespace Information
    {
        //______________________________________________________________________
        //
        //
        //
        //! base class for synchronous stream cipher
        //
        //
        //______________________________________________________________________
        class StreamCipher : public Serializable
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit StreamCipher() noexcept; //!< setup
            virtual ~StreamCipher() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void    restart()                 noexcept = 0; //!< restart inner state
            virtual uint8_t operator()(const uint8_t) noexcept = 0; //!< \return transformed byte

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! transform block from current (no restart())
            /**
             \param target target memory
             \param source source memory
             \param length memory length
             */
            void transform(void * const target, const void * const source, size_t length) noexcept;

        private:
            Y_Disable_Copy_And_Assign(StreamCipher); //!< discarding
        };
    }
}

#endif // !Y_Information_Stream_Cipher_Included

