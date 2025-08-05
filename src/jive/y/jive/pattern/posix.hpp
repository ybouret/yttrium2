//! \file

#ifndef Y_Jive_Pattern_Posix_Included
#define Y_Jive_Pattern_Posix_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //! compiling posix (and alike) patterns
        struct posix
        {

            //------------------------------------------------------------------
            //
            // standard
            //
            //------------------------------------------------------------------
            static Pattern *lower();  //!< \return \verbatim[a-z]\endverbatim
            static Pattern *upper();  //!< \return \verbatim[A-Z]\endverbatim
            static Pattern *alpha();  //!< \return \verbatim[a-zA-Z]\endverbatim
            static Pattern *digit();  //!< \return \verbatim[0-9]\endverbatim
            static Pattern *alnum();  //!< \return \verbatim[a-zA-Z0-9]\endverbatim
            static Pattern *xdigit(); //!< \return \verbatim[0-9a-fA-F]\endverbatim
            static Pattern *blank();  //!< \return \verbatim[ \t]\endverbatim
            static Pattern *space();  //!< \return \verbatim[ \n\r\t\v\f]\endverbatim
            static Pattern *punct();  //!< \return \verbatim][!"#$%&'()*+,./:;<=>?@\^_`{|}~-\endverbatim

            //------------------------------------------------------------------
            //
            // extended
            //
            //------------------------------------------------------------------
            static Pattern *word();      //!< \return \verbatim[a-zA-Z0-9_]\endverbatim
            static Pattern *endl();      //!< \return \verbatim\n|\r|\r\n\endverbatim
            static Pattern *dot();       //!< \return \verbatim^endl\endverbatim
            static Pattern *core();      //!< \return core 7-bits string content, minus quote, dquote  and backslash
            static Pattern *vowel();     //!< \return vowels
            static Pattern *consonant(); //!< \return consonants

            static Pattern *named(const String &);      //!< \return look up pattern by name
            static Pattern *named(const char * const);  //!< \return look up pattern by name
        };
    }
}

#endif
