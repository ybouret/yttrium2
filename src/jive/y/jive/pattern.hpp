
//! \file

#ifndef Y_Jive_Pattern_Included
#define Y_Jive_Pattern_Included 1

#include "y/jive/source.hpp"
#include "y/core/linked/list/cloneable.hpp"
#include "y/graphviz/vizible.hpp"

namespace Yttrium
{
    namespace Jive
    {
        //______________________________________________________________________
        //
        //
        //
        //! Pattern interface
        //
        //
        //______________________________________________________________________
        class Pattern : public Object, public Vizible
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef ListOfCloneable<Pattern> List; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Pattern(const uint32_t) noexcept; //!< setup with uuid
            virtual ~Pattern() noexcept;               //!< cleanup
            Pattern(const Pattern &) noexcept;         //!< copy all but self

            //__________________________________________________________________
            //
            //
            // interface
            //
            //__________________________________________________________________
            virtual Pattern * clone()                    const = 0; //!< \return clone
            virtual bool      accepts(Token &, Source &) const = 0; //!< \return true if accepted


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const uint32_t uuid; //!< identifier
            Pattern *      next; //!< for list
            Pattern *      prev; //!< for list
            void * const   self; //!< original type'

        private:
            Y_Disable_Assign(Pattern); //!< discard
        };



    }

}

#endif
