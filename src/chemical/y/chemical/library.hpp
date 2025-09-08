//! \file


#ifndef Y_Chemical_Library_Included
#define Y_Chemical_Library_Included 1


#include "y/chemical/species.hpp"
#include "y/chemical/type/assembly.hpp"
#include "y/random/bits.hpp"
#include "y/chemical/type/xreal.hpp"
#include "y/graphviz/color-scheme.hpp"

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
            static const char * const         CallSign;       //!< "Library"
            static const char * const         CSID;           //!< "dark28"
            typedef SpeciesDB::ConstIterator  ConstIterator;  //!< alias
            static const int                  LOG10MIN = -20; //!< alias
            static const int                  LOG10MAX =   1; //!< alias
            static xreal_t Concentration(Random::Bits &) noexcept; //!< \return 10^(ran(LOG10MIN:LOG10MAX))


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

            //! fill array with random concentration
            /**
             \param probaZero probility to set a zero concentration
             */
            void conc(Random::Bits &,
                      XWritable    &,
                      const real_t probaZero = 0,
                      const real_t probaNeg  = 0) const;

            //! pretty print
            /**
             \param os output
             \param pfx prefix
             \param arr array for species
             \param sfx suffix
             */
            template <typename ARR> inline
            void print(std::ostream & os,
                       const char *   pfx,
                       const ARR &    arr,
                       const char *   sfx) const
            {
                static const char nope[] = "";
                if(!pfx) pfx = nope;
                if(!sfx) sfx = nope;

                os << '{' << std::endl;
                for(ConstIterator it=db.begin();it!=db.end();++it)
                {
                    const Species &sp = **it;
                    display(os << "  " << pfx,sp.name,Justify::Center) << sfx << " = " << sp(arr,TopLevel) << std::endl;
                }
                os << '}' << std::endl;
            }

            //! pretty print with transform
            /**
             \param os   output
             \param pfx  prefix
             \param arr  array for species
             \param sfx  suffix
             \param proc process each entry
             */
            template <typename ARR, typename PROC> inline
            void print(std::ostream & os,
                       const char *   pfx,
                       const ARR &    arr,
                       const char *   sfx,
                       PROC          &proc) const
            {
                static const char nope[] = "";
                if(!pfx) pfx = nope;
                if(!sfx) sfx = nope;

                os << '{' << std::endl;
                for(ConstIterator it=db.begin();it!=db.end();++it)
                {
                    const Species &sp = **it;
                    display(os << "  " << pfx,sp.name,Justify::Center) << sfx << " = " << proc(sp(arr,TopLevel)) << std::endl;
                }
                os << '}' << std::endl;
            }





        private:
            Y_Disable_Copy_And_Assign(Library); //!< discarding
            Y_Ingress_Decl();                   //!< helper
            SpeciesDB                    db; //!< database
        public:
            const GraphViz::ColorScheme &cs; //!< colorscheme
        };

    }

}

#endif

