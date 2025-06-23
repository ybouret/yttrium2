
//! \file

#ifndef Y_Information_QCodec_Included
#define Y_Information_QCodec_Included 1

#include "y/information/codec.hpp"

namespace Yttrium
{

    namespace Information
    {

        class QCodec : public Codec
        {
        protected:
            explicit QCodec() noexcept;
        public:
            virtual ~QCodec() noexcept;
            class Code;

            virtual bool query(char &C);
            virtual void store(const char C);

        protected:
            void emit(const uint8_t);
            
        private:
            Y_Disable_Copy_And_Assign(QCodec);
            Code * const code;
        };
    }

}

#endif

