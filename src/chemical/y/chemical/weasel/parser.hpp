//! \file


#ifndef Y_Chemical_Weasel_Parser_Included
#define Y_Chemical_Weasel_Parser_Included 1

#include "y/chemical/weasel.hpp"
#include "y/jive/parser.hpp"

namespace Yttrium
{

    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! top level Weasel parser
        //
        //
        //______________________________________________________________________
        class Weasel:: Parser : public Jive::Parser
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Parser();           //!< setup
            virtual ~Parser() noexcept;  //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(Parser); //!< discarding
        };

    }

}

#endif // !Y_Chemical_Weasel_Parser_Included
