
//! \file

#ifndef Y_Ink_Image_Format_Included
#define Y_Ink_Image_Format_Included 1

#include "y/ink/image/codec.hpp"
#include "y/jive/pattern/matching.hpp"
#include "y/pointer/keyed.hpp"

namespace Yttrium
{
    namespace Ink
    {

        //______________________________________________________________________
        //
        //
        //
        //! Speficic Image Format
        //
        //
        //______________________________________________________________________
        class Format : public Codec
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Keyed<String,ArcPtr<Format>> Handle;
            
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param uid format name \param ext extension regular expression
            template <typename UID, typename EXT> inline
            explicit Format(const UID &uid, const EXT &ext) :
            Codec(uid),
            extension(ExtToPattern(ext))
            {

            }

            //! cleanup
            virtual ~Format() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void          renderExtension() const;          //!< helper, save GraphViz extension pattern
            static String LowerCaseExt(const String &path); //!< \param path filename \return lower case path extensoon

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Jive::Matching extension; //!< helper to check matching extension

        private:
            Y_Disable_Copy_And_Assign(Format); //!< discarding

            //! \param ext regular expression \return lower case matching pattern
            template <typename EXT> static inline
            Jive::Pattern * ExtToPattern(const EXT &ext)
            {
                String rx = ext;
                return MakePattern(rx);
            }

            //! \param rx regular expression \return lower case matching pattern
            static Jive::Pattern * MakePattern(String &rx);

        };

    }

}

#endif // !Y_Ink_Image_Format_Included

