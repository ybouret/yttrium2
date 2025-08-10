


#ifndef Y_Jive_Lexical_BString_Included
#define Y_Jive_Lexical_BString_Included 1

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
            //! bracket string
            //
            //
            //__________________________________________________________________
            class BString : public Strings
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const uint32_t       UUID = Y_FOURCC('B','S','T','R'); //!< alias
                static const char           JOIN = '<'; //!< alias
                static const char           QUIT = '>'; //!< alias
                Y_Jive_Plugin_Decl(BString);            //!< alias

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
                explicit BString(const SID    &  sid,
                                 Lexer &         lxr) :
                Strings(UUID,sid,JOIN,QUIT,lxr)
                {
                    initialize();
                    finalize();
                }

                //! cleanup
                virtual ~BString() noexcept;

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
                Y_Disable_Copy_And_Assign(BString); //!< discarding
                void finalize(); //!< register quote and dquote
            };
        }

    }

}

#endif

