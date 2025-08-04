
//! \file

#ifndef Y_Jive_Pattern_Dictionary_Included
#define Y_Jive_Pattern_Dictionary_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {
        class Dictionary
        {
        public:
            explicit Dictionary();
            virtual ~Dictionary() noexcept;

            void operator()(const String &,     Pattern * const); //!< store a new pattern
            void operator()(const char * const, Pattern * const); //!< store a new pattern

            Pattern * query(const char * const) const;
            Pattern * query(const String &)     const;
            
        private:
            class Code;
            Y_Disable_Copy_And_Assign(Dictionary);
            Code * const code;
        };
    }

}

#endif


