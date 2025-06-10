
#include "y/stream/queue.hpp"
#include "y/hexadecimal.hpp"

namespace Yttrium
{
    StreamQueue:: StreamQueue() noexcept :
    OutputStream(),
    IO::Chars() {}

    StreamQueue:: ~StreamQueue() noexcept
    {
    }

    std::ostream & operator<<(std::ostream &os, const StreamQueue &Q)
    {
        for(const IO::Char *ch=Q->head;ch;ch=ch->next)
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
        (*this) << c;
    }

    bool StreamQueue:: query(char &C)
    {
        LiveList &self = *this;
        if(self->size>0)
        {
            C = pullHead();
            return true;
        }
        else
        {
            return false;
        }
    }

    void StreamQueue:: store(const char C)
    {
        (*this) >> C;
    }

}
