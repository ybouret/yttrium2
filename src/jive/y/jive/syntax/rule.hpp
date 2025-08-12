
//! \file

#ifndef Y_Jive_Syntax_Rule_Included
#define Y_Jive_Syntax_Rule_Included 1

#include "y/jive/syntax/node/internal.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {


            class Grammar;

            //__________________________________________________________________
            //
            //
            //
            //! Rule interface
            //
            //
            //__________________________________________________________________
            class Rule : public Object
            {
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
            protected:
                //! setup
                /**
                 \param r rule name
                 \param t rule category
                 \param u rule class identifier
                 */
                template <typename RID> inline
                explicit Rule(const RID     &r,
                              const Category t,
                              const uint32_t u) :
                name(r),
                type(t),
                uuid(u),
                next(0),
                prev(0),
                gptr(0)
                {
                }
                
            public:
                virtual ~Rule() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Tag       name; //!< name
                const Category  type; //!< category
                const uint32_t  uuid; //!< uuid
                Rule *          next; //!< for list
                Rule *          prev; //!< for list
                Grammar * const gptr; //!< owning grammar

            private:
                Y_Disable_Copy_And_Assign(Rule); //!< discarding
            };
        }
    }

}

#endif

