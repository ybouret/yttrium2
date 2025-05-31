
//! \file

#ifndef Y_XML_Element_Included
#define Y_XML_Element_Included 1

#include "y/xml/syntax.hpp"
#include "y/ability/identifiable.hpp"

namespace Yttrium
{
    namespace XML
    {
        class Attribute;

        //______________________________________________________________________
        //
        //
        //
        //! Help to format an Identifiable as an XML element
        //
        //
        //______________________________________________________________________
        class Element : public virtual Identifiable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definition
            //
            //__________________________________________________________________
            typedef XML::Attribute Attribute;
            
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            explicit Element() noexcept; //!< setup
        public:
            virtual ~Element() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods/Helper
            //
            //__________________________________________________________________
            //! write "<callSign" with indentation
            /** \return output stream */
            std::ostream & initProlog(std::ostream &, const size_t) const;

            //! write "/>" if standalone, ">" otherwise
            /**
             \param os output stream
             \param standalone true if standalone element
             \return os << std::endl
             */
            std::ostream & initEpilog(std::ostream &os, const bool standalone=false) const;

            //! write "<callSign>" with indentation
            /** \return output stream */
            std::ostream & init(std::ostream &, const size_t) const;


            //! write "</callSign>" with indentation
            /** \return output stream << std::endl */
            std::ostream & quit(std::ostream &, const size_t) const;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________


            //! display the element with starting indentation
            /**
             \param os output stream
             \param indentation top-level indentation
             */
            virtual void display(std::ostream &os,
                                 size_t        indentation) const = 0;

        private:
            Y_Disable_Copy_And_Assign(Element); //!< discarding
        };

    }
}

#endif
