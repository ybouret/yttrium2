
#include "y/stream/output-queue.hpp"
#include "y/hexadecimal.hpp"

namespace Yttrium
{
    OutputQueue:: OutputQueue() noexcept : IO::Chars() {}

    OutputQueue:: ~OutputQueue() noexcept
    {
    }

    std::ostream & operator<<(std::ostream &os, const OutputQueue &Q)
    {
        for(const IO::Char *ch=Q->head;ch;ch=ch->next)
        {
            const uint8_t c = **ch;
            os << ' ' << Hexadecimal(c).c_str() + 2;
        }
        return os;
    }

    void OutputQueue:: flush()
    {

    }

    void OutputQueue:: write(const char c)
    {
        (*this) << c;
    }
}
