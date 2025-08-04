
//! \file

#ifndef Y_Jive_Pattern_Logic_Included
#define Y_Jive_Pattern_Logic_Included 1

#include "y/jive/pattern.hpp"
#include "y/type/ingress.hpp"

namespace Yttrium
{
    namespace Jive
    {
        //______________________________________________________________________
        //
        //
        //
        //! Logic pattern with operands
        //
        //
        //______________________________________________________________________
        class Logic : public Pattern, public Ingress< const Core::ListOf<Pattern> >
        {
        public:
            typedef Ingress< const Core::ListOf<Pattern> > BaseType; //!< alias


            Logic & operator<<(Pattern * const ) noexcept; //!< append new pattern to operanfs \return *this

            virtual ~Logic() noexcept; //!< cleanup
        protected:
            explicit Logic(const uint32_t) noexcept;  //!< setup
            explicit Logic(const Logic &);            //!< duplicate
            OutputStream & lnk(OutputStream &) const; //!< linking in GraphViz \return output stream
            size_t         srz(OutputStream &) const; //!< serialize operands \return written bytes
            Y_Ingress_Decl();                         //!< alis


            Patterns ops; //!< operands

        private:
            Y_Disable_Assign(Logic); //!< discarding
        };
    }

}


#endif

