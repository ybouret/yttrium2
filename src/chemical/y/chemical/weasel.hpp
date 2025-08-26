//! \file

#ifndef Y_Chemical_Weasel_Included
#define Y_Chemical_Weasel_Included 1


#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/chemical/reactive/equilibria.hpp"
#include "y/chemical/library.hpp"
#include "y/lua++/state.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Weasel Equilibria And Species Elementary Language
        //
        //
        //______________________________________________________________________
        class Weasel : public Singleton<Weasel,ClassLockPolicy>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign;                               //!< "Weasel"
            static const Longevity    LifeTime = LifeTimeOf::ChemicalWeasel; //!< life time

            static const char * const Coef;           //!< "Coef"
            static const char * const RegExp;         //!< "RegExp";
            static const char * const StringID;       //!< "String";
            class Parser;
            class FormulaTranslator;
            class EquilibriumTranslator;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void display(std::ostream &,size_t) const;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            XNode * parse(Jive::Module * const); //!< \return parsed full module to Weasel node

            //__________________________________________________________________
            //
            //
            // Handling Formula
            //
            //__________________________________________________________________
            String  formulaToText(const Formula &, int * const); //!< \return formula to text, with optional charge
            String  formulaToHTML(const Formula &);              //!< \return formula to html
            XNode * formula1(Jive::Module *);                    //!< \return one formula node from compatible module

            //__________________________________________________________________
            //
            //
            // Handling Equilibrium
            //
            //__________________________________________________________________
            Equilibrium *compile(const XNode * const root,
                                 Library     &       lib,
                                 const size_t        top,
                                 Lua::VM            &lvm);

            //__________________________________________________________________
            //
            //
            // Populating
            //
            //__________________________________________________________________
            void operator()(Jive::Module * const, Library &, Equilibria &);

        private:
            Y_Disable_Copy_And_Assign(Weasel); //!< discarding
            friend class Singleton<Weasel,ClassLockPolicy>;

            explicit Weasel();
            virtual ~Weasel() noexcept;
        };
    }
}

#endif

