
//! \file

#ifndef Y_Jive_Syntax_Aggregate_Included
#define Y_Jive_Syntax_Aggregate_Included 1

#include "y/jive/syntax/rule/logical.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            //__________________________________________________________________
            //
            //
            //
            //! Aggregate of existing rules
            //
            //
            //__________________________________________________________________
            class Aggregate : public Logical
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const uint32_t UUID = Y_FOURCC('A', 'G', 'G', '_'); //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param rid rule name
                template <typename RID> inline
                explicit Aggregate(const RID &rid) :
                Logical(rid,UUID)
                {
                }

                //! cleanup
                virtual ~Aggregate() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual bool accepts(Y_Jive_XRule_Args) const;


            private:
                Y_Disable_Copy_And_Assign(Aggregate); //!< discarding
            };
        }

    }

}

#endif

