

#ifndef Y_Jive_Lexical_RString_Included
#define Y_Jive_Lexical_RString_Included 1

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
            //! Raw string, simply quoted
            //
            //
            //__________________________________________________________________
            class RString : public Strings
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const uint32_t       UUID = Y_FOURCC('R','S','T','R'); //!< alias
                static const char           JOIN = '\''; //!< alias
                static Scanner *            Load(InputStream &,Lexer &,TagDB &); //!< loader \return new RString
                Y_Jive_Plugin_Decl(RString);             //!< alias

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
                explicit RString(const SID    &  sid,
                                 Lexer &         lxr) :
                Strings(UUID,sid,JOIN,JOIN,lxr)
                {
                    initialize();
                    finalize();
                }

                //! cleanup
                virtual ~RString() noexcept;
                

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
            private:
                Y_Disable_Copy_And_Assign(RString); //!< discarding
                void finalize(); //!< register dquote
            };
        }

    }

}

#endif

