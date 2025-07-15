
//! \file

#ifndef Y_ASCII_Convert_Included
#define Y_ASCII_Convert_Included 1

#include "y/apex/integer.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/calculus/ipower.hpp"

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
                                   String & fp,
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
                static T Get(const char * const text, const size_t size)
                {
                    bool   sg = false;
                    String ip;
                    String fp;
                    apz    xp;
                    Parsing::FPoint(sg,ip, fp, xp, text, size);
                    std::cerr << "ip='"; Hexadecimal::Display(std::cerr,ip(),ip.size()); std::cerr << "'" << std::endl;
                    std::cerr << "fp='"; Hexadecimal::Display(std::cerr,fp(),fp.size()); std::cerr << "'" << std::endl;
                    std::cerr << "xp='" << xp << "'" << std::endl;

                    const T ten(10);
                    const T tenth(0.1);

                    T res = 0;
                    {
                        const size_t ips = ip.size();
                        for(size_t i=1;i<=ips;++i)
                        {
                            res *= ten;
                            res += static_cast<T>( ip[i] );
                        }
                    }

                    {
                        const size_t fps = fp.size();
                        T            fac = tenth;
                        for(size_t i=1;i<=fps;++i,fac *= tenth)
                        {
                            res += fac * static_cast<T>(fp[i]);
                        }
                    }

                    {
                        int xpi = 0; if(!xp.tryCast(xpi)) Parsing::Overflow();
                        switch(xp.s)
                        {
                            case __Zero__: break;
                            case Positive: res *= ipower(ten,   size_t( xpi) ); break;
                            case Negative: res *= ipower(tenth, size_t(-xpi) ); break;
                        }
                    }

                    if(sg)
                    {
                        switch( Sign::Of(res) )
                        {
                            case __Zero__: break;
                            case Negative:
                            case Positive:
                                res = -res;
                                break;
                        }
                    }
                    return res;
                }


            };

        };
    }

}

#endif

