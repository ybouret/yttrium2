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

        std::ostream & Assemblies:: display(std::ostream &os, const Components &eq) const
        {
            nameFmt.display(os,eq.name,      Justify::Center);
            os << " : ";
            reacFmt.display(os,eq.reac.name, Justify::Right);
            os << ' ' << Components::Arrows << ' ';
            prodFmt.display(os,eq.prod.name, Justify::Left);
            os << " : ";
            return os;
        }


    }

}

