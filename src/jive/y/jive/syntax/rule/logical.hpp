
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
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
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

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual OutputStream & vizPost(OutputStream &) const;


                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                Logical & operator<<(const char);   //!< append marker from Parser  \return *this
                Logical & operator<<(const Rule &); //!< append rule (from Parser)  \return *this

            private:
                Y_Disable_Copy_And_Assign(Logical); //!< discarding
            };

        }

    }

}

#endif

