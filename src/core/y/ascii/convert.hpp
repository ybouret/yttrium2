
//! \file

#ifndef Y_ASCII_Convert_Included
#define Y_ASCII_Convert_Included 1

#include "y/apex/integer.hpp"
//#include "y/string.hpp"

namespace Yttrium
{

    namespace ASCII
    {
        namespace Conversion
        {

            struct Parsing
            {
                static void Overflow();
                static void FPoint(bool &   sg,
                                   String & ip,
                                   apn &    fp,
                                   size_t & fl,
                                   apz &    xp,
                                   const char * const text,
                                   const size_t       size);
            };

            template <typename T>
            T Parse(const char * const text, const size_t size);

            template <typename T>
            struct DirectParser
            {
                static T Get(const char *const text, const size_t size)
                {
                    return Parse<T>(text,size);
                }
            };


            //! for signed/unsigned
            template <typename T>
            struct AProxyParser
            {
                typedef typename Pick< IsSigned<T>::Value, apz, apn>::Type apType;

                static T Get(const char * const text, const size_t size)
                {
                    const apType ans = DirectParser<apType>::Get(text,size);
                    T            res(0);
                    if(!ans.tryCast(res)) Parsing::Overflow();
                    return res;
                }
            };


            template <typename T>
            struct FPointParser
            {
#if 0
                static T Get(const char * const text, const size_t size)
                {
                    apz    ip;
                    apn    fp;
                    size_t fl=0;
                    apz    xp;
                    Parsing::FPoint(ip, fp, fl, xp, text, size);

                    int64_t  ii = 0; if(!ip.tryCast(ii)) Parsing::Overflow();
                    uint64_t ff = 0; if(!fp.tryCast(ff)) Parsing::Overflow();
                    int64_t  xx = 0; if(!xp.tryCast(xx)) Parsing::Overflow();

                }
#endif

            };

        };
    }

}

#endif

