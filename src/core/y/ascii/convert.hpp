
//! \file

#ifndef Y_ASCII_Convert_Included
#define Y_ASCII_Convert_Included 1

#include "y/apex/integer.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/calculus/ipower.hpp"

#include "y/type/conversion.hpp"
#include "y/type/alternative.hpp"
#include "y/exception.hpp"


namespace Yttrium
{

    namespace ASCII
    {
        namespace Conversion
        {

            //__________________________________________________________________
            //
            //
            //
            //! Parsing helpers
            //
            //
            //__________________________________________________________________
            struct Parsing
            {
                static void Overflow(); //!< throw overflow

                //! split floating point parts
                /**
                 \param sg sign
                 \param ip string of [0..9]s
                 \param fp string of [0..9]s
                 \param xp exponent
                 \param text original test
                 \param size original size
                 */
                static void FPoint(bool &   sg,
                                   String & ip,
                                   String & fp,
                                   apz &    xp,
                                   const char * const text,
                                   const size_t       size);
            };

            //! direct parsing function \return Apex::Numberb
            template <typename T>
            T Parse(const char * const, const size_t);


            //__________________________________________________________________
            //
            //
            //! Direct parser for ap[n|z]
            //
            //__________________________________________________________________
            template <typename T>
            struct DirectParser
            {
                //! direct parse
                /**
                 \param text original test
                 \param size original size
                 \return parsed value
                 */
                static T Get(const char *const text, const size_t size)
                {
                    return Parse<T>(text,size);
                }
            };


            //__________________________________________________________________
            //
            //
            //! Proxy for unsigned/signed integral
            //
            //__________________________________________________________________
            template <typename T>
            struct AProxyParser
            {
                typedef typename Pick< IsSigned<T>::Value, apz, apn>::Type apType; //!< alias

                //!  parse thru apex proxy
                /**
                 \param text original test
                 \param size original size
                 \return parsed and casted value
                 */
                static T Get(const char * const text, const size_t size)
                {
                    const apType ans = DirectParser<apType>::Get(text,size);
                    T            res(0);
                    if(!ans.tryCast(res)) Parsing::Overflow();
                    return res;
                }
            };

            //__________________________________________________________________
            //
            //
            //!  Floating Point Parser
            //
            //__________________________________________________________________
            template <typename T>
            struct FPointParser
            {
                //! split and compute result
                /**
                 \param text original test
                 \param size original size
                 \return parsed and computed value
                 */
                static T Get(const char * const text, const size_t size)
                {
                    bool   sg = false;
                    String ip;
                    String fp;
                    apz    xp;
                    Parsing::FPoint(sg,ip, fp, xp, text, size);

                    const T ten(10);
                    const T tenth(0.1f);

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

        }


        //______________________________________________________________________
        //
        //
        //!  Generic conversion
        //
        //______________________________________________________________________
        struct Convert
        {


            //! select and call conversion function
            /**
             \param text original test
             \param size original size
             \return parsed and computed value according to type
             */
            template <typename T>
            static inline T Parse(const char * const text, const size_t size)
            {
                typedef typename TypeTraits<T>::MutableType MutableType;
                static const bool IsApNumber = Y_Is_SuperSubClass_Strict(Apex::Number,MutableType);
                static const bool IsIntegral = TypeTraits<MutableType>::IsIntegral;
                typedef typename Alternative<IsApNumber,Conversion::DirectParser<T>,
                IsIntegral,Conversion::AProxyParser<T>,Conversion::FPointParser<T> >::Type API;
                return API::Get(text,size);
            }

            //! parse user's data
            /**
             \param text user's string
             \param varName optional variable name
             \return parsed value
             */
            template <typename T> static inline
            T To(const String &text, const char * const varName = 0)
            {
                try {
                    return Parse<T>(text.c_str(),text.size());
                }
                catch(Exception &excp)
                {
                    if(varName) excp.add(" for %s", varName);
                    throw excp;
                }
                catch(...)
                {
                    throw;
                }
            }

            //! parse c-string
            /**
             \param text user's string
             \param varName optional variable name
             \return parsed value
             */
            template <typename T> static inline
            T To(const char * const text, const char * const varName = 0)
            {
                const String _(text);
                return To<T>(_,varName);
            }

        };


    }

}

#endif

