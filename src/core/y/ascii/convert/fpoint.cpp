
#include "y/ascii/convert.hpp"
#include "y/system/exception.hpp"
#include "y/check/usual.hpp"

namespace Yttrium
{

    namespace ASCII
    {

        namespace Conversion
        {
            void Parsing::FPoint(apz &ip, apn &fp, apz &xp, const char *const text, const size_t size)
            {
                static const char fn[] = "ASCII<Floating Point>";
                assert(0==ip);
                assert(0==fp);
                assert(0==xp);
                assert(Good(text,size));

                if(size<=0) throw Specific::Exception(fn,"no input");
                const char * const last = text + size;
                const char *       curr = text;
                bool neg = false;
                if('-'== *curr)
                {
                    if(++curr>=last) throw Specific::Exception(fn,"no input after '-");
                    neg  = true;
                }

                size_t ipLength = 0;
                while(curr<last)
                {
                    const char c = *(curr++);
                    switch(c)
                    {
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9':
                            ip *= 10;
                            ip += int64_t(c-'0');
                            ++ipLength;
                            continue;
                        default:
                            throw Specific::Exception(fn,"unexpected '%c' in integer part",c);
                    }
                }
                goto RETURN;


            RETURN:
                if(neg) (void) ip.neg();



            }
        }

    }

}

