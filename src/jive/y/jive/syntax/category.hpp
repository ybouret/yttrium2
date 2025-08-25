
//! \file


#ifndef Y_Jive_Syntax_Category_Included
#define Y_Jive_Syntax_Category_Included 1

#include "y/object/counted.hpp"
#include "y/graphviz/vizible.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {

            //! named category
            enum Category
            {
                IsTerminal, //!< for terminal rule/node
                IsInternal  //!< for internal rule/node
            };

            //__________________________________________________________________
            //
            //
            //
            //! Base class for Node/Rule
            //
            //
            //__________________________________________________________________
            class Category_ : public CountedObject, public Vizible
            {
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
            protected:
                explicit Category_(const Category) noexcept; //!< setup

            public:
                virtual ~Category_() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                bool isInternal() const noexcept; //!< \return type == IsInternal
                bool isTerminal() const noexcept; //!< \return type == IsTerminal


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Category type; //!< category

            private:
                Y_Disable_Copy_And_Assign(Category_); //!< discarding
            };
        }
    }
}

#endif
