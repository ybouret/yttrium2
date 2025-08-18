
//! \file

#ifndef Y_Jive_Context_Included
#define Y_Jive_Context_Included 1

#include "y/jive/tag.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Context to locate entities
        //
        //
        //______________________________________________________________________
        class Context
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Context(const Tag &) noexcept; //!< setup
            virtual ~Context()            noexcept; //!< cleanup
            Context(const Context &)      noexcept; //!< duplicate

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            String    str() const; //!< \return "tag:line:column:"

            Context & dot()  noexcept; //!< increase column \return *this
            Context & endl() noexcept; //!< new line        \return *this

            void stamp(Exception &) const; //!< stamp exception

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Tag    tag;      //!< identifier
            const size_t line;     //!< current line
            const size_t column;   //!< current column


        private:
            Y_Disable_Assign(Context); //!< discarding
        };

    }

}

#endif

