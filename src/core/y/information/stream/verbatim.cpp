
#include "y/information/stream/verbatim.hpp"

namespace Yttrium
{
    namespace Information
    {

        Verbatim:: Encoder:: Encoder() noexcept
        {

        }

        Verbatim:: Encoder:: ~Encoder() noexcept
        {

        }

        void Verbatim:: Encoder:: restart() noexcept
        {
        }

        uint8_t Verbatim:: Encoder:: operator()(uint8_t b) noexcept
        {
            return b;
        }

        size_t Verbatim:: Encoder:: serialize(OutputStream &) const
        {
            return 0;
        }
    }

}


