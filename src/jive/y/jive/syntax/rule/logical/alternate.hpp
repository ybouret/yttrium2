

//! \file

#ifndef Y_Jive_Syntax_Alternate_Included
#define Y_Jive_Syntax_Alternate_Included 1

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
            //! Choice of existing rules
            //
            //
            //__________________________________________________________________
            class Alternate : public Logical
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const uint32_t UUID = Y_FOURCC('A', 'L', 'T', '_'); //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param rid rule name
                template <typename RID> inline
                explicit Alternate(const RID &rid) :
                Logical(rid,UUID)
                {
                }


                virtual ~Alternate() noexcept; //!< cleanup

            private:
                Y_Disable_Copy_And_Assign(Alternate); //!< discardin
            };
        }

    }

}

#endif

