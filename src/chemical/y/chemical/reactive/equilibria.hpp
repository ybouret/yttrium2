
//! \file

#ifndef Y_Chemical_Equilibria_Included
#define Y_Chemical_Equilibria_Included 1


#include "y/chemical/reactive/equilibrium.hpp"
#include "y/chemical/type/assemblies.hpp"
#include "y/graphviz/color-scheme.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        typedef SuffixSet<String,Equilibrium::Pointer> EqDB; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Database of Equilibria
        //
        //
        //______________________________________________________________________
        class Equilibria : public Ingress< const EqDB>, public Assemblies, public Freezable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const   CallSign;      //!< "Equilibria"
            typedef EqDB::ConstIterator ConstIterator; //!< alias
            typedef EqDB::Iterator      Iterator;      //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Equilibria();          //!< setup
            virtual ~Equilibria() noexcept; //!< cleanup
            Y_OSTREAM_PROTO(Equilibria);    //!< display

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Iterator begin()         noexcept; //!< \return db.begin
            Iterator end()           noexcept; //!< \return db.end
            size_t   nextTop() const noexcept; //!< \return next index for equilibrium

            //! record \param eq a new equilibrium \return *eq
            template <typename EQ> inline
            EQ & operator()(EQ * const eq)
            {
                assert(0!=eq);
                record(eq);
                return *eq;
            }




        private:
            Y_Disable_Copy_And_Assign(Equilibria); //!< discarding
            Y_Ingress_Decl();                      //!< helper
            void    record(Equilibrium * const);   //!< check and record
            EqDB    db; //!< database

        };


    }

}

#endif

