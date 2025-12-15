#include "y/color/conv.hpp"
#include "y/color/gray.hpp"
#include "y/color/x11.hpp"

#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"
#include "y/format/hexadecimal.hpp"

#include <cstring>

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
        // generate float table
        OutputFile fp("gray.hxx");

        for(unsigned i=0;i<256;++i)
        {
            fp("Y_U(%u)",i);
            if(i<255) fp << ',';
            fp << '\n';
        }

    }

    if(false)
    {
        static const size_t size = 1+3*255;
        uint8_t             gtab[size];
        memset(gtab,0,sizeof(gtab));
        for(unsigned r=0;r<256;++r)
        {
            for(unsigned g=0;g<256;++g)
            {
                for(unsigned b=0;b<256;++b)
                {
                    const unsigned sum = r + g + b; Y_ASSERT(sum<size);
                    unsigned val = sum/3;     Y_ASSERT(val<=255);
                    if( (val <= 0) && (r||g||b) ) val = 1;
                    gtab[sum] = (uint8_t) val;
                }
            }
        }
        Hexadecimal::Display(std::cerr,gtab,size) << std::endl;

        OutputFile fp("gtab.hxx");
        for(unsigned i=0;i<size;++i)
        {
            fp("0x%02x",gtab[i]);
            if(i<size-1) fp << ',';
            fp << "\n";
        }
    }

    {
        uint8_t  lmax = 0;
        for(unsigned r=0;r<256;++r)
        {
            for(unsigned g=0;g<256;++g)
            {
                for(unsigned b=0;b<256;++b)
                {
                    const uint8_t level = Color::Gray::ToByte( (uint8_t)r, (uint8_t)g, (uint8_t)b );
                    if(level>lmax) lmax=level;
                }
            }
        }
        std::cerr << "lmax=" << Hexadecimal(lmax) << std::endl;
    }

    std::cerr << "#X11 = " << Color::X11Color::Count << std::endl;


}
Y_UDONE()

