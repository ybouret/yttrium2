
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
            throw Specific::Exception(CallSign,"not implemented");
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

                    case RBRACK:
                        if(motif->size<=0) throw Specific::Exception(CallSign,"empty bank in '%s'",expr);
                        return motif.yield();

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

