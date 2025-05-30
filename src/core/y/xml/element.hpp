
//! \file

#ifndef Y_XML_Element_Included
#define Y_XML_Element_Included 1

#include "y/xml/syntax.hpp"
#include "y/ability/identifiable.hpp"

namespace Yttrium
{
    namespace XML
    {

        class Element : public virtual Identifiable
        {
        protected:
            explicit Element() noexcept;
        public:
            virtual ~Element() noexcept;


            //! write "<callSign"
            std::ostream & initProlog(std::ostream &os, const size_t) const;

            //! write "/>" if standalone, ">" otherwise
            std::ostream & initEpilog(std::ostream &os, const bool standAlone=false) const;

            //! write "<callSign>
            std::ostream & init(std::ostream &, const size_t) const;


            //! write "</callSign>
            std::ostream & quit(std::ostream &, const size_t) const;

            virtual void display(std::ostream &os,
                                 const size_t  indentation) const = 0;

        private:
            Y_Disable_Copy_And_Assign(Element);
        };

    }
}

#endif
