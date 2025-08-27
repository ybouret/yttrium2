//! \file


#ifndef Y_Chemical_Library_Included
#define Y_Chemical_Library_Included 1


#include "y/chemical/species.hpp"
#include "y/chemical/type/assembly.hpp"
#include "y/random/bits.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        typedef SuffixSet<String,Species::Pointer> SpeciesDB; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Library of species
        //
        //
        //______________________________________________________________________
        class Library : public Ingress< const SpeciesDB >, public Assembly
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const         CallSign;      //!< "Library"
            typedef SpeciesDB::ConstIterator  ConstIterator;  //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Library();            //!< setup empty
            virtual ~Library() noexcept;   //!< cleanup
            Y_OSTREAM_PROTO(Library);      //!< display

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            const Species & operator[](const String &);        //!< \return on the fly new/old species
            const Species & operator[](const String &) const;  //!< \return existing species

            const Species & operator[](const char * const);       //!< \return wrapper
            const Species & operator[](const char * const) const; //!< \return wrapper

            const Species & operator[](const Formula &); //!< \return species from formula


        private:
            Y_Disable_Copy_And_Assign(Library); //!< discarding
            Y_Ingress_Decl();                   //!< helper
            SpeciesDB db; //!< database
        };

    }

}

#endif

