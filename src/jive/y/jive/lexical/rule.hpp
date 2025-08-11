
//! \file

#ifndef Y_Jive_Lexical_Rule_Included
#define Y_Jive_Lexical_Rule_Included 1

#include "y/jive/token.hpp"
#include "y/jive/pattern.hpp"
#include "y/core/linked/list/cxx.hpp"

namespace Yttrium
{
    namespace Jive
    {
        class TagDB;

        namespace Lexical
        {


            //__________________________________________________________________
            //
            //
            //! property of produced tokens (Emit/Drop)
            //
            //__________________________________________________________________
            enum Property
            {
                DropToken, //!< with discard token
                SpawnUnit, //!< will emit a new unit
                SendToken, //!< will send token to specific treatment
                BadSyntax  //!< will stop scanner and throw exception
            };

            //__________________________________________________________________
            //
            //
            //! take action upon returned demeanor
            //
            //__________________________________________________________________
            enum Demeanor
            {
                Emit, //!< emit a lexeme
                Drop, //!< drop detected token
                Send, //!< send detected token
                Halt, //!< syntax error
                Call, //!< call a new scanner
                Back  //!< back to calling scanner
            };

            //__________________________________________________________________
            //
            //
            //! Attribute for rule/motif
            //
            //__________________________________________________________________
            enum Attribute
            {
                Regular, //!< doesn't count as new line
                NewLine  //!< count as new line
            };



            //__________________________________________________________________
            //
            //
            //
            //! Rule = name + motif + flags
            //
            /**
             - EOF
             - standard: emit/drop
             - control:  jump/back
             */
            //
            //__________________________________________________________________
            class Rule : public Object, public Serializable
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef CxxListOf<Rule> List; //!< alias
                static const char * HumarReadableDeed(const Demeanor)  noexcept; //!< \return readadble demeanor
                static const char * HumarReadableAttr(const Attribute) noexcept; //!< \return readable attribute
                static const char * HumanReadablePpty(const Property)  noexcept; //!< \return readable property

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup a producing rule
                /**
                 \param usrTag   will be rule name
                 \param usrMotif will be rule motid
                 \param usrAttr  control source
                 \param property what to do when token is produced
                 \param noData   empty tag
                 */
                Rule(const Tag       &usrTag,
                     const Motif     &usrMotif,
                     const Attribute  usrAttr,
                     const Property   property,
                     const Tag  &     noData)  noexcept;


                //! setup a control rule
                /**
                 if data length is 0, it's a Back, otherwise it's a Call
                 \param usrTag   will be rule name
                 \param usrMotif will be rule motid
                 \param usrAttr  control source
                 \param usrData  compatible for tag.
                 */
                template <typename DATA>
                Rule(const Tag       &usrTag,
                     const Motif     &usrMotif,
                     const Attribute  usrAttr,
                     const DATA &     usrData) :
                name(usrTag),
                motif(usrMotif),
                attr(usrAttr),
                data(usrData),
                deed(data->length()>0 ? Call : Back),
                next(0),
                prev(0)
                {
                }


                virtual ~Rule()   noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual size_t serialize(OutputStream&) const;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                void binaryPattern() const; //!< save pattern to name.bin
                void renderPattern() const; //!< save pattern to name.dot and render to name.png

                const char * humanReadableDeed() const noexcept; //!< \return readable deed
                const char * humanReadableAttr() const noexcept; //!< \return readable attr


                static Rule * Load(InputStream &, TagDB &); //!< \return reloaded rule

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Tag       name;  //!< name
                const Motif     motif; //!< motif to match
                const Attribute attr;  //!< attribute
                const Tag       data;  //!< optional data
                const Demeanor  deed;  //!< demeanor
                Rule *          next;  //!< for list
                Rule *          prev;  //!< for list
                
            private:
                Y_Disable_Copy_And_Assign(Rule); //!< discarding

                //! construct from full data for reload
                Rule(const Tag &,
                     const Motif &,
                     const Attribute,
                     const Tag &,
                     const Demeanor);
            };
        }
    }

}

#endif

