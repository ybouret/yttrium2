
//! \file

#ifndef Y_ASCII_Convert_Included
#define Y_ASCII_Convert_Included 1

#include "y/apex/integer.hpp"
#include "y/type/traits.hpp"

namespace Yttrium
{

    namespace ASCII
    {
        namespace Conversion
        {

            struct Parsing
            {
                static void Overflow();
                static void FPoint(apz  &ip,
                                   apn  &fp,
                                   apz  &xp,
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



        };
    }

}

#endif

