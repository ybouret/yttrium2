
#include "y/stream/queue.hpp"
#include "y/hexadecimal.hpp"

namespace Yttrium
{
    StreamQueue:: StreamQueue() noexcept :
    OutputStream(), q()
    {}

    StreamQueue:: ~StreamQueue() noexcept
    {
    }

    std::ostream & operator<<(std::ostream &os, const StreamQueue &Q)
    {
        for(const IO::Char *ch=Q.q->head;ch;ch=ch->next)
        {
            const uint8_t c = **ch;
            os << ' ' << Hexadecimal(c).c_str() + 2;
        }
        return os;
    }

    void StreamQueue:: flush()
    {

    }

    void StreamQueue:: write(const char c)
    {
        q << uint8_t(c);
    }

    void StreamQueue:: frame(const void * const addr, const size_t size)
    {
        assert( Good(addr,size) );
        const uint8_t * p = static_cast<const uint8_t *>(addr);
        for(size_t i=size;i>0;--i) q << *(p++);
    }

    bool StreamQueue:: query(char &C)
    {
        if(q->size>0)
        {
            C = char(q.pullHead());
            return true;
        }
        else
        {
            return false;
        }
        }

    void StreamQueue:: store(const char C)
    {
        q >> uint8_t(C);
    }

}
