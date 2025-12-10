#include "y/color/rgb.hpp"
#include "y/color/rgba.hpp"

#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"

using namespace Yttrium;

template <typename T> static inline
void ShowOpaque(const char * const name)
{
    Color::Print<T>(std::cerr << "Opaque<" << name << "> = ",Color::Opaque<T>::Value) << std::endl;
}

#define SHOW_OPAQUE(TYPE) ShowOpaque<TYPE>( #TYPE )

Y_UTEST(colors)
{
    SHOW_OPAQUE(float);
    SHOW_OPAQUE(double);
    SHOW_OPAQUE(long double);
    SHOW_OPAQUE(uint8_t);
    SHOW_OPAQUE(uint16_t);
    SHOW_OPAQUE(uint32_t);
    SHOW_OPAQUE(uint64_t);

    if(false)
    {
        OutputFile fp("gray.hxx");

        for(unsigned i=0;i<256;++i)
        {
            fp("Y_U(%u)",i);
            if(i<255) fp << ',';
            fp << '\n';
        }

    }

}
Y_UDONE()

