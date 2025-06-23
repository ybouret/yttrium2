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

            virtual void reset() noexcept = 0;

        private:
            Y_Disable_Copy_And_Assign(Codec);
        };
    }

}


#endif

