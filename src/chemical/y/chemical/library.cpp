#include "y/chemical/library.hpp"
#include <iomanip>
#include "y/core/display.hpp"


namespace Yttrium
{
    namespace Chemical
    {


        xreal_t Library:: Concentration(Random::Bits &ran) noexcept
        {
            static const real_t xpmin = LOG10MIN;
            static const real_t xpmax = LOG10MAX;
            const real_t        u     = ran.to<real_t>();
            const real_t        xp    = xpmin * u + xpmax * (1.0-u);
            return pow(10.0,xp);
        }

        void Library:: conc(Random::Bits &ran,
                            XWritable    &C,
                            const real_t probaZero,
                            const real_t probaNeg) const
        {
            for(ConstIterator it=db.begin();it!=db.end();++it)
            {
                const Species &sp = **it;
                if( ran.to<real_t>() < probaZero )
                    sp(C,TopLevel) = 0;
                else
                {
                    sp(C,TopLevel) = Concentration(ran);
                    if( ran.to<real_t>() < probaNeg )
                        sp(C,TopLevel) = -sp(C,TopLevel);
                }
            }

        }



        Library:: ~Library() noexcept
        {
        }

        Library:: Library() :
        Ingress<const SpeciesDB>(),
        Assembly(),
        db(),
        cs( GraphViz::ColorScheme::Query(CSID) )
        {
        }

        Y_Ingress_Impl(Library,db)

        const char * const Library:: CallSign = "Library";
        const char * const Library:: CSID     = "dark28";
        
        const Species & Library:: operator[](const String &id)
        {

            if(Species::Pointer * const pps = db.search(id)) return **pps;

            const Species::Pointer p = new Species(id,db.size()+1);
            if(!db.insert(p)) throw Specific::Exception(CallSign,"multiple '%s'", id.c_str());
            enroll(*p);
            return *p;
        }

        const Species & Library:: operator[](const String &id) const
        {
            if( const Species::Pointer * const pps = db.search(id)) return **pps;
            throw Specific::Exception(CallSign,"no '%s'", id.c_str());
        }

        const Species & Library:: operator[](const char * const id)
        {
            const String _(id);
            return (*this)[_];
        }

        const Species & Library:: operator[](const char * const id) const
        {
            const String _(id);
            return (*this)[_];
        }

        const Species & Library:: operator[](const Formula &f)
        {
            const String id = f.text(0);
            return (*this)[ id ];
        }

        std::ostream & operator<<(std::ostream &os, const Library &lib)
        {
            os << '{' << std::endl;
            for(Library::ConstIterator it=lib->begin();it!=lib->end();++it)
            {
                const Species &sp = **it;
                lib.display(os << "    |",sp.name,Justify::Left)
                << "| z = " << std::setw(4) << sp.z
                << " | indx=";
                Core::Display(os,sp.indx,sp.MaxLevel);
                os << std::endl;
            }
            return os << '}';
        }

    }

}
