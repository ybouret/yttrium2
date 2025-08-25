
//! \file

#ifndef Y_Jive_DSL_Included
#define Y_Jive_DSL_Included

#include "y/jive/parser.hpp"
#include "y/ability/identifiable.hpp"

namespace Yttrium
{

    namespace Jive
    {
        //______________________________________________________________________
        //
        //
        //
        //! Domain Specific Language
        //
        //
        //______________________________________________________________________
        class DSL : public Identifiable
        {
        protected:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setuo \param id language name
            template <typename ID> inline
            explicit DSL(const ID &id) : lang(id)
            {
            }

        public:
            virtual ~DSL() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const char * callSign() const noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            const String & key() const noexcept; //!< \return *lang


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Tag lang; //!< language name

        private:
            Y_Disable_Copy_And_Assign(DSL); //!< discarding
        };
    }


}


#endif

