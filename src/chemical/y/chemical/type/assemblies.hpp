
//! \file


#ifndef Y_Chemical_Assemblies_Included
#define Y_Chemical_Assemblies_Included 1


#include "y/chemical/type/assembly.hpp"
#include "y/chemical/reactive/components.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        class Assemblies
        {
        public:
            explicit Assemblies() noexcept;
            virtual ~Assemblies() noexcept;


            void enroll(const Components &) noexcept;

            //std::ostream & display(std::ostream &os, const Components &) const;


            const Assembly nameFmt;
            const Assembly reacFmt;
            const Assembly prodFmt;

        private:
            Y_Disable_Copy_And_Assign(Assemblies);
        };

    }

}

#endif

