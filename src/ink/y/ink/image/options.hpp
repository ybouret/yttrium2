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
        typedef ArcPtr<String>           Option;   //!< alias
        typedef SuffixMap<String,Option> OptionDB; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! named options for Formats
        //
        //
        //______________________________________________________________________
        class Options : public OptionDB
        {
        public:
            static const char * const CallSign; //!< "Ink::Options"


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Options();                   //!< setup
            Options(const Options &);    //!< duplicate
            virtual ~Options() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            String & operator[](const String &);     //!< \return on the fly/created option string
            String & operator[](const char * const); //!< \return on the fly/created option string

            const String & operator[](const String &)     const; //!< \return existing option string
            const String & operator[](const char * const) const; //!< \return existing option string


            static const String * Query(const Options * const, const String &) noexcept; //!< \return pointer to existing string, NULL othersize
            static const String * Query(const Options * const, const char * const);      //!< \return pointer to existing string, NULL othersize

        private:
            Y_Disable_Assign(Options); //!< discarding
        };

    }

}

#endif // !Y_Ink_Image_Options_Included
