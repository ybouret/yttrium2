
#include "y/stream/queue.hpp"
#include "y/hexadecimal.hpp"

namespace Yttrium
{
    StreamQueue:: StreamQueue() noexcept :
    OutputStream() //,     IO::Chars()
    {}

    StreamQueue:: ~StreamQueue() noexcept
    {
    }

    std::ostream & operator<<(std::ostream &os, const StreamQueue &Q)
    {
#if 0
        for(const IO::Char *ch=Q->head;ch;ch=ch->next)
        {
            const uint8_t c = **ch;
            os << ' ' << Hexadecimal(c).c_str() + 2;
        }
#endif
        return os;
    }

    void StreamQueue:: flush()
    {

    }

    void StreamQueue:: write(const char c)
    {
        //(*this) << uint8_t(c);
    }

    bool StreamQueue:: query(char &C)
    {
#if 0
        IO::Chars &self = *this;
        if(self->size>0)
        {
            C = char(pullHead());
            return true;
        }
        else
        {
            return false;
        }
#endif
    }

    void StreamQueue:: store(const char C)
    {
        //(*this) >> uint8_t(C);
    }

}
