
#include "y/jive/pattern/matching.hpp"
#include "y/jive/regexp.hpp"


namespace Yttrium
{
    namespace Jive
    {
        Matching:: Matching(Pattern * const p) noexcept :
        Token(),
        motif(p),
        fc(motif->firstChars())
        {
            
        }


        Matching:: Matching(const String &rx) :
        Token(),
        motif( RegExp::Compile(rx) ),
        fc(motif->firstChars())
        {

        }


        Matching:: Matching(const char * const rx) :
        Token(),
        motif( RegExp::Compile(rx) ),
        fc(motif->firstChars())
        {

        }


        Matching:: ~Matching() noexcept
        {
        }

        bool Matching:: found(const Request request, Module * const input)
        {
            Source source(input);
            free(); assert(0==size);
            switch(request)
            {
                case Exactly: return exactly_(source);
                case Somehow: return somehow_(source);
            }
            return false;
        }

        bool Matching:: exactly_(Source &source)
        {
            assert(0==size);
            if(!motif->accepts(*this,source)) return false; // no acceptation
            if(source.ready())                return false; // extraneous data
            return true;
        }

        bool Matching:: somehow_(Source &source)
        {
            // forward
        FORWARD:
            assert(0==size);
            const Char * const first = source.peek();
            if(!first) return false;
            if( !fc.getbit(**first) )
            {
                source.sweep(1);
                goto FORWARD;
            }

            // try
            if(motif->accepts(*this,source)) return true;
            assert(0==size);
            source.sweep(1);
            goto FORWARD;

        }

        Matching:: Matching(const Matching &other) noexcept :
        Token(),
        motif(other.motif),
        fc(other.fc)
        {
        }
        




    }

}
