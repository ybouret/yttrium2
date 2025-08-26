
//! \file

#ifndef Y_Chemical_Equilibria_Included
#define Y_Chemical_Equilibria_Included 1


#include "y/chemical/reactive/equilibrium.hpp"
#include "y/chemical/type/assemblies.hpp"
#include "y/lua++/state.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        typedef SuffixSet<String,Equilibrium::Pointer> EqDB; //!< alias


        class Equilibria : public Ingress< const EqDB>, public Assemblies
        {
        public:
            static const char * const   CallSign;
            typedef EqDB::ConstIterator ConstIterator;

            explicit Equilibria();
            virtual ~Equilibria() noexcept;

            size_t nextTop() const noexcept;

            template <typename EQ> inline
            EQ & operator()(EQ * const eq)
            {
                assert(0!=eq);
                record(eq);
                return *eq;
            }



        private:
            Y_Disable_Copy_And_Assign(Equilibria);
            Y_Ingress_Decl();
            void    record(Equilibrium * const);

            EqDB    db;

        public:
            Lua::VM lvm;
        };


    }

}

#endif

