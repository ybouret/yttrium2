//! \file

#ifndef Y_Information_Codec_Included
#define Y_Information_Codec_Included 1

#include "y/stream/input.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{

    namespace Information
    {
        class Codec : public InputStream, public OutputStream
        {
        protected:
            explicit Codec() noexcept;
            
        public:
            virtual ~Codec() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Codec);
        };
    }

}


#endif

