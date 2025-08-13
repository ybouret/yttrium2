
//! \file


#ifndef Y_Jive_Syntax_Category_Included
#define Y_Jive_Syntax_Category_Included 1

#include "y/object.hpp"

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

            class Category_ : public Object
            {
            protected:
                explicit Category_(const Category) noexcept;

            public:
                virtual ~Category_() noexcept;

                bool isInternal() const noexcept; //!< \return type == IsInternal
                bool isTerminal() const noexcept; //!< \return type == IsTerminal

                const Category type;
                
            private:
                Y_Disable_Copy_And_Assign(Category_);
            };
        }
    }
}

#endif
