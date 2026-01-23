//! \file

#ifndef Y_Ink_Image_Options_Included
#define Y_Ink_Image_Options_Included 1

#include "y/string.hpp"
#include "y/container/associative/suffix/map.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{
    namespace Ink
    {
        typedef ArcPtr<String>           Option;
        typedef SuffixMap<String,Option> OptionDB;

        class Options : public OptionDB
        {
        public:
            static const char * const CallSign; //!< "Ink::Options"


            Options();
            Options(const Options &);
            virtual ~Options() noexcept;

            String & operator[](const String &);
            String & operator[](const char * const);

            const String & operator[](const String &)     const;
            const String & operator[](const char * const) const;

            static const String * Query(const Options * const, const String &) noexcept;
            static const String * Query(const Options * const, const char * const);
            
        private:
            Y_Disable_Assign(Options);
        };

    }

}

#endif // !Y_Ink_Image_Options_Included
