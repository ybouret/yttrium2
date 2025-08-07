
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
        namespace Lexical
        {

            enum Demeanor
            {
                Emit,
                Drop,
                Call,
                Back
            };

            enum Attribute
            {
                Regular,
                NewLine
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
            class Rule : public Object
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef CxxListOf<Rule> List; //!< alias

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
                 \param emitting produce unit if true, discard if false
                 \param noData   empty tag
                 */
                Rule(const Tag       &usrTag,
                     const Motif     &usrMotif,
                     const Attribute  usrAttr,
                     const bool       emitting,
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
            };
        }
    }

}

#endif

