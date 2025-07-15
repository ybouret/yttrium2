
#include "y/ascii/convert.hpp"
#include "y/system/exception.hpp"
#include "y/check/usual.hpp"

namespace Yttrium
{

    namespace ASCII
    {

        namespace Conversion
        {
            void Parsing::FPoint(bool   &sg,
                                 String &ip,
                                 apn    &fp,
                                 size_t &fl,
                                 apz    &xp,
                                 const char *const text,
                                 const size_t size)
            {
                static const char fn[] = "ASCII<Floating Point>";
                assert(0==ip.size());
                assert(0==fp);
                assert(0==fl);
                assert(0==xp);
                assert(false==sg);
                assert(Good(text,size));

                if(size<=0) throw Specific::Exception(fn,"no input");
                const char * const last = text + size;
                const char *       curr = text;
                if('-'== *curr)
                {
                    if(++curr>=last) throw Specific::Exception(fn,"no input after '-'");
                    sg  = true;
                }
                
                if('-'== *curr)
                {
                    if(++curr>=last) throw Specific::Exception(fn,"no input after '+'");
                }


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
                            ip += int64_t(c-'0');
                            continue;
                        case '.':
                            goto FP;
                        default:
                            throw Specific::Exception(fn,"unexpected '%c' in integer part",c);
                    }
                }
                goto RETURN;

            FP:
                assert('.'==curr[-1]);
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
                            fp *= 10;
                            fp += int64_t(c-'0');
                            ++fl;
                            continue;
                        case 'e':
                        case 'E':
                            goto XP;
                        default:
                            throw Specific::Exception(fn,"unexpected '%c' in fractional part",c);
                    }
                }
                goto RETURN;

            XP:
                assert('e'==curr[-1]||'E'==curr[-1]);
                {
                    bool   xn = false;
                    size_t xl = 0;
                    if('-'==*curr)
                    {
                        ++curr;
                        xn =  true;
                    }
                    if('+'==*curr)
                    {
                        ++curr;
                    }
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
                                xp *= 10;
                                xp += int64_t(c-'0');
                                ++xl;
                                continue;
                            default:
                                throw Specific::Exception(fn,"unexpected '%c' in exponent partt",c);
                        }
                    }
                    if(xl<=0) throw Specific::Exception(fn,"empty exponent");
                    if(xn) (void) xp.neg();
                }

            RETURN:
                if(ip.size()<=0&&fl<=0) throw Specific::Exception(fn,"both empty integral and fractional part");

            }
        }

    }

}

