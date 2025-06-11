
#include "y/sorting/heap.hpp"
#include "y/check/usual.hpp"
#include <cstring>

namespace Yttrium{

    namespace Sorting
    {
        void  Heap::Sort(void * const arr,
                         const size_t num,
                         const size_t alen,
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
                uint8_t * const ra  = ra1-alen;
                size_t          l   = (num>>1)+1;
                size_t          ir  = num;
                for(;;)
                {
                    if(l>1)
                    {
                        const size_t offset = --l * alen;
                        memcpy(rra,&ra[offset],alen);
                    }
                    else
                    {
                        void * const ra_ir = &ra[ir*alen];
                        memcpy(rra,ra_ir,alen);
                        memcpy(ra_ir,ra1,alen);
                        if (--ir == 1)
                        {
                            memcpy(ra1,rra,alen);
                            break;
                        }
                    }
                    {
                        size_t i=l;
                        size_t j=l+l;
                        while(j<=ir)
                        {
                            if ( (j<ir) && proc(&ra[j*alen],&ra[(j+1)*alen],args) < 0 )
                                ++j;

                            if( proc(rra,&ra[j*alen],args)<0 )
                            {
                                memcpy(&ra[i*alen],&ra[j*alen],alen);
                                i=j;
                                j <<= 1;
                            }
                            else
                                break;
                        }
                        memcpy(&ra[i*alen],rra,alen);
                    }
                }
            }
        }
    }

}
