//! \file

#ifndef Y_Cameo_Summator_Included
#define Y_Cameo_Summator_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{

    namespace Cameo
    {

        template <typename T>
        class Summator
        {
        public:
            Y_Args_Declare(T,Type);
        protected:
            inline explicit Summator() noexcept {}
        public:
            inline virtual ~Summator() noexcept {}

            virtual void ldz() noexcept = 0;


        private:
            Y_Disable_Copy_And_Assign(Summator);
        };
        
    }
}

#endif
