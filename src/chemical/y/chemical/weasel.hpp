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
        class Weasel : public Singleton<Weasel,ClassLockPolicy>, public Lua::VM
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
            class DiffusionCoefficientsTable;
            
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
            String  formulaToLaTeX(const Formula &);             //!< \return formula to LaTeX
            XNode * formula1(Jive::Module *);                    //!< \return one formula node from compatible module
            XNode * parseFormula(const String &);                //!< \return one formula from name

            //__________________________________________________________________
            //
            //
            // Handling Equilibrium
            //
            //__________________________________________________________________

            //! creating a new equilibrium
            /**
             \param root equilibrium node
             \param lib  library
             \param top  index for new equilibrium
             \param lvm  lua state
             \return new equilibrium
             */
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

            //! process module into regexp, species, equilibria...
            void operator()(Jive::Module * const, Library &, Equilibria &);

            //! query diffusion coefficient for given species
            /**
             \param name species name
             \return value from table, -1 if not found
             */
            double diffusionCoefficient(const String &name) const noexcept;



        private:
            Y_Disable_Copy_And_Assign(Weasel); //!< discarding
            friend class Singleton<Weasel,ClassLockPolicy>;

            explicit Weasel();
            virtual ~Weasel() noexcept;

            void onRegExp(const String &, Library &, Equilibria &); //!< process regular expression
        };
    }
}

#endif // !Y_Chemical_Weasel_Included

