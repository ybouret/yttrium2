//! \file

#ifndef Y_Jive_Pattern_Joker_Included
#define Y_Jive_Pattern_Joker_Included 1

#include "y/jive/pattern.hpp"


namespace Yttrium
{
    namespace Jive
    {
        //______________________________________________________________________
        //
        //
        //
        //! Joker
        //
        //
        //______________________________________________________________________
        class Joker : public Pattern
        {
        public:
            virtual ~Joker() noexcept; //!< cleanup

        protected:
            explicit Joker(const uint32_t, const Motif &); //!< setup with a STRONG motif
            explicit Joker(const Joker &) noexcept;        //!< cleanup

        private:
            Y_Disable_Assign(Joker); //!< discarding

        public:
            const Motif motif; //!< acting motif
        };
    }

}


#endif

