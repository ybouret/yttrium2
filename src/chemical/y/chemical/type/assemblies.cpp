#include "y/chemical/type/assemblies.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        Assemblies:: ~Assemblies() noexcept
        {
        }

        Assemblies:: Assemblies() noexcept :
        nameFmt(), reacFmt(), prodFmt()
        {
        }


        void Assemblies::  enroll(const Components &eq) noexcept
        {
            Coerce(nameFmt).enroll(eq);
            Coerce(reacFmt).enroll(eq.reac);
            Coerce(prodFmt).enroll(eq.prod);
        }

    }

}

