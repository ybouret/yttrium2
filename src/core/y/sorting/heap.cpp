
#include "y/sorting/heap.hpp"
#include "y/check/usual.hpp"
#include <cstring>

namespace Yttrium{

    namespace Sorting
    {
        void  Heap::Sort(void * const arr,
                         const size_t num,
                         const size_t width,
                         void * const rra,
                         int        (*proc)(const void * const, const void * const, void *),
                         void * const args
                         )
        {
            assert( Good(arr,num) );
            assert(0!=proc);
            assert(0!=rra);

            if (num<2)
                return;
            else
            {
                assert(0!=arr);
                uint8_t * const ra1 = (uint8_t *)arr;
                uint8_t * const ra  = ra1-width;
                size_t          l   = (num>>1)+1;
                size_t          ir  = num;
                for(;;)
                {
                    if(l>1)
                    {
                        const size_t offset = --l * width;
                        memcpy(rra,&ra[offset],width);
                    }
                    else
                    {
                        void * const ra_ir = &ra[ir*width];
                        memcpy(rra,ra_ir,width);
                        memcpy(ra_ir,ra1,width);
                        if (--ir == 1)
                        {
                            memcpy(ra1,rra,width);
                            break;
                        }
                    }
                    {
                        size_t i=l;
                        size_t j=l+l;
                        while(j<=ir)
                        {
                            if ( (j<ir) && proc(&ra[j*width],&ra[(j+1)*width],args) < 0 )
                                ++j;

                            if( proc(rra,&ra[j*width],args)<0 )
                            {
                                memcpy(&ra[i*width],&ra[j*width],width);
                                i=j;
                                j <<= 1;
                            }
                            else
                                break;
                        }
                        memcpy(&ra[i*width],rra,width);
                    }
                }
            }
        }
    }

}
