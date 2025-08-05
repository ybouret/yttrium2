
#include "y/jive/regexp/compiler.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/pointer/auto.hpp"
#include "y/system/exception.hpp"
#include "y/jive/pattern/posix.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Pattern * RegExp:: Compiler:: goPosix()
        {
            assert(':' == curr[0]);
            assert(LBRACK == curr[-1]);

            const char * const ini = curr+1;
            while(true)
            {
                if(++curr>=last) goto BAD;
                if(':' == *curr)
                {
                    const char * const end = curr;
                    if(++curr>=last)         goto BAD; // skipping ':'
                    if(RBRACK != *(curr++) ) goto BAD; // skipping ']'

                    const String id(ini,end-ini);
                    if(id.size()<=0) throw Specific::Exception(CallSign,"empty posix alias in '%s'",expr);
                    return posix::named(id);
                }
            }

        BAD:
            throw Specific::Exception(CallSign,"unfinished posix alias in '%s'",expr);
        }

        Pattern * RegExp::Compiler:: subBank()
        {
            assert( LBRACK == curr[-1] );
            AutoPtr<Logic> motif;
            if(curr>=last) goto UNFINISHED;

            // initialize
            switch(*curr)
            {
                case CARET:
                    motif = new None();
                    if(++curr>=last) goto UNFINISHED;
                    if('-' == *curr) {
                        *motif << new Byte('-');
                        ++curr;
                    }
                    break;

                case '-':
                    motif = new Or();
                    *motif << new Byte('-');
                    ++curr;
                    break;

                case ':':
                    return goPosix();

                default:
                    motif = new Or();
                    break;

            }

            while(curr<last)
            {
                const char C = *(curr++);

                switch(C)
                {

                    case LBRACK:
                        *motif << subBank();
                        break;

                    case RBRACK:
                        if(motif->size<=0) throw Specific::Exception(CallSign,"empty bank in '%s'",expr);
                        return motif.yield();

                    case BACKSLASH:
                        *motif << escBank();
                        break;

                    default:
                        *motif << new Byte(C);
                        break;
                }

            }



            return 0;

        UNFINISHED:
            throw Specific::Exception(CallSign,"unfinished bank in '%s'", expr);


        }
    }

}

