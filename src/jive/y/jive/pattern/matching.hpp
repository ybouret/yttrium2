
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
            enum Request
            {
                Exactly,
                Somehow
            };

            Matching(Pattern * const)  noexcept; //!< setup
            Matching(const Matching &) noexcept; //!< duplicate
            virtual ~Matching() noexcept;        //!< cleanup
            Matching(const char * const);
            Matching(const String &);

            bool  found(const Request, Module * const);

            template <typename NAME>
            bool  found(const Request      request,
                        const NAME &       name,
                        const char * const buffer,
                        const size_t       buflen)
            {
                return found(request, Module::OpenData(name,buffer,buflen));
            }

            template <typename NAME>
            bool  found(const Request      request,
                        const NAME &       name,
                        const char * const buffer)
            {
                return found(request, Module::OpenData(name,buffer,StringLength(buffer)));
            }

            template <typename NAME>
            bool  found(const Request      request,
                        const NAME &       name,
                        const String &     buffer)
            {
                return found(request, Module::OpenData(name,buffer) );
            }






            const Motif      motif;
            const FirstChars fc;

        private:
            Y_Disable_Assign(Matching);
            bool exactly_(Source&);
            bool somehow_(Source&);
        };
    }

}

#endif

