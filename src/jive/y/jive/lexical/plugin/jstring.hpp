
#ifndef Y_Jive_Lexical_JString_Included
#define Y_Jive_Lexical_JString_Included 1

#include "y/jive/lexical/plugin/strings.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            //__________________________________________________________________
            //
            //
            //
            //! JSON/C string doubly quoted
            //
            //
            //__________________________________________________________________
            class JString : public Strings
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const uint32_t       UUID = Y_FOURCC('J','S','T','R'); //!< alias
                static const char           JOIN = '"'; //!< alias
                Y_Jive_Plugin_Decl(JString);            //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param sid associated scanner name
                 \param lxr root lexer
                 */
                template <typename SID> inline
                explicit JString(const SID    &  sid,
                                 Lexer &         lxr) :
                Strings(UUID,sid,JOIN,JOIN,lxr)
                {
                    initialize();
                    finalize();
                }

                //! cleanup
                virtual ~JString() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual size_t serialize(OutputStream &fp) const;


                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
            private:
                Y_Disable_Copy_And_Assign(JString); //!< discarding
                void finalize(); //!< register quote
            };
        }

    }

}

#endif

