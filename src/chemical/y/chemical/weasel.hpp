//! \file

#ifndef Y_Chemical_Weasel_Included
#define Y_Chemical_Weasel_Included 1


#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/chemical/formula.hpp"

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
            static const char * const CallSign;
            static const Longevity    LifeTime = LifeTimeOf::ChemicalWeasel;
            static const char * const      Coef;           //!< "Coef"
            static const char * const      RegExp;         //!< "RegExp";
            static const char * const      StringID;       //!< "String";
            class Parser;

            virtual void display(std::ostream &,size_t) const;

            XNode * parse( Jive::Module *);


        private:
            Y_Disable_Copy_And_Assign(Weasel); //!< discarding
            friend class Singleton<Weasel,ClassLockPolicy>;

            explicit Weasel();
            virtual ~Weasel() noexcept;
        };
    }
}

#endif

