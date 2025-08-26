
#include "y/chemical/reactive/components.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        const char * const Components:: Arrows   = "<=>";
        const char * const Components:: Prod     = "Prod";
        const char * const Components:: Reac     = "Reac";

        Components:: ~Components() noexcept
        {
        }

        std::ostream & operator<<(std::ostream &os, const Components &self)
        {
            return os << '@' << self.name << ':' << self.reac.name << self.Arrows << self.prod.name;
        }

        void Components:: p(const unsigned nu, const Species &sp)
        {
            if(prod.has(sp)) throw Specific::Exception(name.c_str(),"multiple product '%s'", sp.name.c_str());
            if(reac.has(sp)) throw Specific::Exception(name.c_str(),"already reactant '%s'", sp.name.c_str());
            Coerce(prod).add(nu,sp);
        }

        void Components:: r(const unsigned nu, const Species &sp)
        {
            if(prod.has(sp)) throw Specific::Exception(name.c_str(),"already product '%s'", sp.name.c_str());
            if(reac.has(sp)) throw Specific::Exception(name.c_str(),"multiple reactant '%s'", sp.name.c_str());
            Coerce(reac).add(nu,sp);
        }


        void Components:: p(const Species &sp) { p(1,sp); }
        void Components:: r(const Species &sp) { r(1,sp); }

    }

}

