

//! \file

#ifndef Y_Ink_Format_PNM_Included
#define Y_Ink_Format_PNM_Included 1

#include "y/ink/image/format.hpp"

namespace Yttrium
{
    namespace Ink
    {


        //______________________________________________________________________
        //
        //
        //
        //! Portable aNyMap Format
        //
        //
        //______________________________________________________________________
        class FormatPNM : public Format
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign;  //!< "BMP"
            static const char * const Extension; //!< "p[bgp]m"

            //! supported Kind of PNM
            enum Kind
            {
                P1, //!< b/w, text
                P2, //!< g/s, text
                P3, //!< rgb, test
                P4, //!< todo
                P5, //!< todo
                P6  //!< todo
            };

            //! deduce kind from request
            /**
             \param lowerCaseExt desired extension
             \param binary       if desired binary representation
             \return matching kind
             */
            static Kind GetKind(const String &lowerCaseExt, const bool binary);

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit FormatPNM();           //!< setup
            virtual ~FormatPNM() noexcept;  //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________

            //! saving
            /**
             \param image image
             \param fileName output file name
             \param options  possible options
             options are:
             - 'binary=[on|off]'
             - 'zoom=x[,y]'
             */
            virtual void  onSave(const Image   &       image,
                                 const String  &       fileName,
                                 const Options * const options) const;


            virtual Image onLoad(const String &, const Options * const) const;

        private:
            Y_Disable_Copy_And_Assign(FormatPNM); //!< discarding
        };
    }

}

#endif // !Y_Ink_Format_PNM_Included

