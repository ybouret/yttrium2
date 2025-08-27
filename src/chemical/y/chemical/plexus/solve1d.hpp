//! \file


#ifndef Y_Chemical_Solve1D_Included
#define Y_Chemical_Solve1D_Included 1


#include "y/chemical/reactive/components.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        class Solve1D
        {
        public:
            static const char * const CallSign;
            
            explicit Solve1D();
            virtual ~Solve1D() noexcept;

            xreal_t operator()(const Components &E,
                               const xreal_t     K,
                               XWritable        &C,
                               const Level       L,
                               const XReadable  &C0);

        private:
            class Code;
            Y_Disable_Copy_And_Assign(Solve1D);
            Code * const code;
        };
    }

}

#endif

