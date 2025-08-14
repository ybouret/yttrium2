
//! \file

#ifndef Y_Jive_Syntax_Logical_Included
#define Y_Jive_Syntax_Logical_Included 1

#include "y/jive/syntax/rule/internal.hpp"
#include "y/protean/bare/light/list.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            typedef Protean::BareLightList<Rule> Manifest; //!< alias
            typedef Manifest::NodeType           RuleNode; //!< alias
            
            //__________________________________________________________________
            //
            //
            //
            //! Logical rule: manifest of existing rules
            //
            //
            //__________________________________________________________________
            class Logical : public Internal, public Manifest
            {
            protected:
                //! setup \param r rule name \param u rule class identifiers
                template <typename RID> inline
                explicit Logical(const RID &r, const uint32_t u) :
                Internal(r,u),
                Manifest()
                {
                }

                
            public:
                virtual ~Logical() noexcept; //!< cleanup

                virtual OutputStream & vizPost(OutputStream &) const;
            private:
                Y_Disable_Copy_And_Assign(Logical); //!< discarding
            };

        }

    }

}

#endif

