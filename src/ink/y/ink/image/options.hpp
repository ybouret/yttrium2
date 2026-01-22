//! \file

#ifndef Y_Ink_Image_Options_Included
#define Y_Ink_Image_Options_Included 1

#include "y/string.hpp"
#include "y/container/associative/suffix/map.hpp"

namespace Yttrium
{
    namespace Ink
    {
        typedef SuffixMap<String,String> OptionDB;

        class Options : public OptionDB
        {
        public:
            Options();
            Options(const Options &);
            virtual ~Options() noexcept;

            

        private:
            Y_Disable_Assign(Options);
        };

    }

}

#endif // !Y_Ink_Image_Options_Included
