
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

        class Attribute
        {
        public:
            typedef void (*DisplayNameProc)(std::ostream &, const void * const);
            typedef void (*DisplayDataProc)(std::ostream &, const void * const, const int);


            template <typename NAME, typename DATA> inline
            Attribute(const NAME & name, const DATA &data, const int w = 0) noexcept :
            hName( &name ),
            hData( &data ),
            width( w     ),
            dName( DisplayName<NAME> ),
            dData( DisplayData<DATA> )
            {
            }


            ~Attribute() noexcept;
            Attribute(const Attribute &) noexcept;
            Y_OSTREAM_PROTO(Attribute);

        private:
            Y_Disable_Assign(Attribute);
            const void * const    hName;
            const void * const    hData;
            const int             width;
            DisplayNameProc const dName;
            DisplayDataProc const dData;

            template <typename T> static inline void DisplayName(std::ostream &     os,
                                                                 const void * const addr)
            {
                assert(0!=addr);
                os << *static_cast<const T *>(addr);
            }

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

