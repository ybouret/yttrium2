
//! \file

#ifndef Y_ASCII_Convert_Included
#define Y_ASCII_Convert_Included 1

#include "y/apex/integer.hpp"

namespace Yttrium
{

    namespace ASCII
    {
        namespace Conversion
        {

            struct Parsing
            {
                static void Overflow();
            };

            template <typename T>
            T Parse(const char * const text, const size_t size);



            template <typename T,bool>
            struct ParseIntegral;



            //! unsigned
            template <typename T>
            struct ParseIntegral<T,false>
            {
                static inline T From(const char * const text, const size_t size)
                {
                    const apn n = Parse<apn>(text,size);
                    T         res(0);
                    if(!n.tryCast(res)) Parsing::Overflow();
                    return res;
                }
            };

            //! signed
            template <typename T>
            struct ParseIntegral<T,true>
            {
                static inline T From(const char * const text, const size_t size)
                {
                    const apz z = Parse<apz>(text,size);
                    T         res(0);
                    if(!z.tryCast(res)) Parsing::Overflow();
                    return res;
                }
            };




        };
    }

}

#endif

