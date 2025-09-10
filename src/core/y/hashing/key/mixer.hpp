
//! \file

#ifndef Y_Hashing_KeyMixer_Included
#define Y_Hashing_KeyMixer_Included 1


#include "y/hashing/des64.hpp"

namespace Yttrium
{

    namespace Hashing
    {

        //______________________________________________________________________
        //
        //
        //
        //! Primitive type mixing to form key
        //
        //
        //______________________________________________________________________
        class KeyMixer
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definition
            //
            //__________________________________________________________________
            typedef DES64 MixerType; //!< 64-bits mixing

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit KeyMixer() noexcept; //!< setup
            virtual ~KeyMixer() noexcept; //!< cleanup

            //! data to size_t
            /**
             \param data any POD data
             \return key from mixing
             */
            template <typename T> inline
            size_t operator()( T & data ) noexcept
            {
                return mixer.mix<T,size_t>(data);
            }


        private:
            Y_Disable_Copy_And_Assign(KeyMixer); //!< discarding
            MixerType mixer; //!< inner mixing
        };
    }

}

#endif

