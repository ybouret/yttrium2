//! \file

#ifndef Y_Jive_Tag_Included
#define Y_Jive_Tag_Included 1

#include "y/string.hpp"
#include "y/pointer/keyed.hpp"
#include "y/pointer/arc.hpp"
#include "y/type/copy-of.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //! base string pointer for tag
        typedef Keyed<String, ArcPtr<const String> > TagType;

        //______________________________________________________________________
        //
        //
        //
        //! Tag for multiple string references
        //
        //
        //______________________________________________________________________
        class Tag : public TagType, public Serializable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Jive::Tag"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Tag(String * const) noexcept; //!< direct setup
            Tag(const Tag &)    noexcept; //!< duplicate
            Tag(const String &);          //!< setup
            Tag(const char * const);      //!< setup
            Tag(const char);              //!< setup
            virtual ~Tag()      noexcept; //!< cleanup
            Tag(InputStream &);           //!< load

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual size_t serialize(OutputStream &) const;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Tag & operator+=( const Tag & );       //!< \return *this += tag
            Tag & operator+=( const String & );    //!< \return *this += string
            Tag & operator+=( const char * const); //!< \return *this += text
            Tag & operator+=( const char );        //!< \return *this += char

        private:
            Y_Disable_Assign(Tag); //!< discarding
        };

    }
}

#endif

