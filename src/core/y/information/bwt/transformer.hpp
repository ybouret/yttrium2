
//! \file

#ifndef Y_Information_BWT_Transformer_Included
#define Y_Information_BWT_Transformer_Included 1


#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Information
    {

        class BWT_Transformer
        {
        public:
            class Code;
            explicit BWT_Transformer() noexcept;
            virtual ~BWT_Transformer() noexcept;

            size_t encode(void * const       target,
                          const void * const source,
                          const size_t       length);

            void   decode(void * const       target,
                          const void * const source,
                          const size_t       length,
                          const size_t       primary);

        private:
            Y_Disable_Copy_And_Assign(BWT_Transformer);
            Code *code;

            void make(const size_t length);
        };
    }

}

#endif

