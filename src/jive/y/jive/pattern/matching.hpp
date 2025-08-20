
//! \file

#ifndef Y_Jive_Pattern_Matching_Included
#define Y_Jive_Pattern_Matching_Included 1

#include "y/jive/pattern.hpp"
#include "y/jive/pattern/first-chars.hpp"
#include "y/string/length.hpp"

namespace Yttrium
{
    namespace Jive
    {


        //______________________________________________________________________
        //
        //
        //
        //! Matching data
        //
        //
        //______________________________________________________________________
        class Matching : public Token
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________

            //! request type
            enum Request
            {
                Exactly, //!< full source must match
                Somehow  //!< found an occurence
            };

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Matching(Pattern * const)  noexcept; //!< setup
            Matching(const Matching &) noexcept; //!< duplicate
            virtual ~Matching() noexcept;        //!< cleanup
            Matching(const char * const);        //!< setup with regular expression
            Matching(const String &);            //!< setup with regular expression

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return true if request if fullfilled within module
            bool  found(const Request, Module * const);


            //! buffer lookup
            /**
             \param request request
             \param name    data name
             \param buffer  buffer address
             \param buflen  buffer lentgth
             \return true iff request if fullfilled
             */
            template <typename NAME>
            bool  found(const Request      request,
                        const NAME &       name,
                        const char * const buffer,
                        const size_t       buflen)
            {
                return found(request, Module::OpenData(name,buffer,buflen));
            }

            //! text lookup
            /**
             \param request request
             \param name    data name
             \param text    C-string
             \return true iff request if fullfilled
             */
            template <typename NAME>
            bool  found(const Request      request,
                        const NAME &       name,
                        const char * const text)
            {
                return found(request, Module::OpenData(name,text,StringLength(text)));
            }

            //! string lookup
            /**
             \param request request
             \param name    data name
             \param text    String
             \return true iff request if fullfilled
             */
            template <typename NAME>
            bool  found(const Request      request,
                        const NAME &       name,
                        const String &     text)
            {
                return found(request, Module::OpenData(name,text) );
            }



            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Motif      motif; //!< motif
            const FirstChars fc;    //!< first chars

        private:
            Y_Disable_Assign(Matching); //!< discarding
            bool exactly_(Source&);     //!< \return true iff matched all source
            bool somehow_(Source&);     //!< \return true iff found one occurence
        };
    }

}

#endif

