
//! \file


#ifndef Y_Chemical_Species_Included
#define Y_Chemical_Species_Included 1


#include "y/chemical/type/indexed.hpp"
#include "y/chemical/formula.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        class Species : public Formula, public Indexed
        {
        public:
            explicit Species(const Formula &, const size_t top);
            virtual ~Species() noexcept;
            explicit Species(const String &,     const size_t top);
            explicit Species(const char * const, const size_t top);


            const int z;
        private:
            Y_Disable_Copy_And_Assign(Species);
        };

    }

}

#endif

