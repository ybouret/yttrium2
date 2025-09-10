
//! \file

#ifndef Y_Hashing_KeyMixer_Included
#define Y_Hashing_KeyMixer_Included 1


#include "y/hashing/des64.hpp"

namespace Yttrium
{

    namespace Hashing
    {

        class KeyMixer
        {
        public:
            typedef DES64 MixerType;
            explicit KeyMixer() noexcept;
            virtual ~KeyMixer() noexcept;

            template <typename T> inline
            size_t operator()( T & data ) noexcept
            {
                return mixer.mix<T,size_t>(data);
            }


        private:
            Y_Disable_Copy_And_Assign(KeyMixer);
            MixerType mixer;
        };
    }

}

#endif

