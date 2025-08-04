//! \file

#ifndef Y_Jive_Pattern_Joker_Included
#define Y_Jive_Pattern_Joker_Included 1

#include "y/jive/pattern.hpp"


namespace Yttrium
{
    namespace Jive
    {

        class Joker : public Pattern
        {
        public:
            virtual ~Joker() noexcept;

        protected:
            explicit Joker(const uint32_t, const Motif &) noexcept;
            explicit Joker(const Joker &) noexcept;

        private:
            Y_Disable_Assign(Joker);

        public:
            const Motif motif;
        };
    }

}


#endif

