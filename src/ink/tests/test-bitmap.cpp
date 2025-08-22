
#include "y/ink/bitmap.hpp"
#include "y/utest/run.hpp"
#include "y/container/contiguous.hpp"
#include "y/random/park-miller.hpp"

using namespace Yttrium;

namespace
{
    template <typename T> class SomeRow
    {
    public:

        T & operator[](const unit_t i) noexcept
        {
            assert(p);
            assert(i>=x);
            assert(i<=xt);
            return p[i];
        }


    private:
        T * const    p;
    public:
        const size_t w;
        const unit_t x;
        const unit_t xt;

    private:
        SomeRow() noexcept;
        ~SomeRow() noexcept;
        Y_Disable_Copy_And_Assign(SomeRow);
    };
}

Y_UTEST(bitmap)
{
    Random::ParkMiller ran;
    Ink::Bitmap bmp(100,34,sizeof(uint32_t));

    Y_SIZEOF(Ink::BitRow);

    for(unit_t j=0;j<bmp.upper.y;++j)
    {
        Ink::BitRow &       r   = bmp(j);
        SomeRow<uint32_t> & row = (SomeRow<uint32_t>&)(r);
        for(unit_t i=row.x;i<=row.xt;++i)
        {
            row[i] = ran.to<uint32_t>();
        }
    }

}
Y_UDONE()
