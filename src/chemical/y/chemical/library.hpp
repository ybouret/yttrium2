//! \file


#ifndef Y_Chemical_Library_Included
#define Y_Chemical_Library_Included 1


#include "y/chemical/species.hpp"
#include "y/chemical/type/assembly.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        typedef SuffixSet<String,Species::Pointer> SpeciesDB;

        class Library : public Ingress< const SpeciesDB >, public Assembly
        {
        public:
            static const char * const   CallSign;
            typedef SpeciesDB::ConstIterator ConstIterator;

            explicit Library();
            virtual ~Library() noexcept;
            Y_OSTREAM_PROTO(Library);

            const Species & operator[](const String &);
            const Species & operator[](const String &) const;
            
            const Species & operator[](const char * const);
            const Species & operator[](const char * const) const;

            const Species & operator[](const Formula &);


        private:
            Y_Disable_Copy_And_Assign(Library);
            Y_Ingress_Decl();
            SpeciesDB db;
        };

    }

}

#endif

