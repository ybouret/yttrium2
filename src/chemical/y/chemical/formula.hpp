//! \file


#ifndef Y_Chemical_Formula_Included
#define Y_Chemical_Formula_Included 1


#include "y/chemical/weasel/types.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! Species Formula, keep parsed Xnode
        //
        //
        //______________________________________________________________________
        class Formula
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Formula"
            static const char * const Name;     //!< "Name"
            static const char * const Body;     //!< "Body"
            static const char * const Mult;     //!< "Mult"
            static const char * const Z;        //!< "Z"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Formula(XNode * const)  noexcept; //!< setup
            Formula(const XCode &)  noexcept; //!< setup
            Formula(const Formula&) noexcept; //!< duplicate
            virtual ~Formula()      noexcept; //!< cleanup
            Formula(const String &);          //!< parsed and compile name

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            String text(int * const z) const; //!< \param z optional charge address \return converted to text
            String html()              const; //!< \return converted to html
            String laTeX()             const; //!< \return converted to LaTeX

            static String ToText(const String &);  //!< \return description to text
            static String ToHTML(const String &);  //!< \return decription to html
            static String ToLaTeX(const String &); //!< \return description to latex

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const XCode code; //!< shared binary representation
        private:
            Y_Disable_Assign(Formula); //!< discarding
        };

    }

}

#endif // !Y_Chemical_Formula_Included

