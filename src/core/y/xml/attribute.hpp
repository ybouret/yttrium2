
//! \file

#ifndef Y_XML_Attribute_Included
#define Y_XML_Attribute_Included 1

#include "y/xml/syntax.hpp"
#include "y/ostream-proto.hpp"
#include <iomanip>
#include <cassert>

namespace Yttrium
{
    namespace XML
    {

        //______________________________________________________________________
        //
        //
        //
        //! in-place format of an attribute
        //
        //
        //______________________________________________________________________
        class Attribute
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef void (*DisplayNameProc)(std::ostream &, const void * const);            //!< alias
            typedef void (*DisplayDataProc)(std::ostream &, const void * const, const int); //!< alias


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! prepare attribute
            /**
             \param name a std::ostream compatible name
             \param data a std::ostream compatible data
             \param w    optional std::setw value
             */
            template <typename NAME, typename DATA> inline
            Attribute(const NAME & name, const DATA &data, const int w = 0) noexcept :
            hName( &name ),
            hData( &data ),
            width( w     ),
            dName( DisplayName<NAME> ),
            dData( DisplayData<DATA> )
            {
            }


            ~Attribute()                 noexcept; //!< cleanup
            Attribute(const Attribute &) noexcept; //!< duplicate
            Y_OSTREAM_PROTO(Attribute);            //!< display

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
        private:
            Y_Disable_Assign(Attribute); //!< discarding
            const void * const    hName; //!< address of name
            const void * const    hData; //!< address of data
            const int             width; //!< std::setw parameter
            DisplayNameProc const dName; //!< display name proc
            DisplayDataProc const dData; //!< display daya proc

            //! generic name display
            /**
             \param os  output
             \param addr address of name
             */
            template <typename T> static inline void DisplayName(std::ostream &     os,
                                                                 const void * const addr)
            {
                assert(0!=addr);
                os << *static_cast<const T *>(addr);
            }

            
            //! generic data display
            /**
             \param os   output
             \param addr address of data
             \param w   std::setw(w) if w>0
            */
            template <typename T> static inline void DisplayData(std::ostream &     os,
                                                                 const void * const addr,
                                                                 const int          w)
            {
                assert(0!=addr);
                if(w>0) os << std::setw(w);
                os << *static_cast<const T *>(addr);
            }

        };
    }

}

#endif

