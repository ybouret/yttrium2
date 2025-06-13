
#include "y/sorting/index.hpp"
#include "y/check/usual.hpp"

namespace Yttrium
{
    namespace Sorting
    {
        void Index:: Make(size_t * const idx,
                          const size_t   num,
                          void * const   arr,
                          const size_t   alen,
                          Compare const  proc,
                          void * const   args)
        {
            assert(Good(idx,num));
            assert(Good(arr,num));
            assert(alen>0);
            //------------------------------------------------------------------
            // initialize indices
            //------------------------------------------------------------------
            for(size_t i=num;i>0;--i) idx[i] = i;

            //------------------------------------------------------------------
            // sort routine
            //------------------------------------------------------------------
            {
                size_t   inc = 1;
                do
                {
                    inc *=3;
                    ++inc;
                }
                while( inc <= num );
                do
                {
                    inc /= 3;
                    for( size_t i=inc+1;i<=num;++i)
                    {
                        const size_t   t = idx[i];
                        const T       &v = arr[t];
                        size_t         j = i;
                        size_t         d = j-inc;
                        assert( t      <= n );
                        assert( idx[d] <= n );
                        while( cmp( v, arr[ idx[d] ] ) == Negative )
                        {
                            idx[j] = idx[d];
                            j = d;
                            if( j <= inc )
                                break;
                            d -= inc;
                        }
                        idx[ j ] = t;
                    }
                }
                while( inc > 1 );
            }

        }
    }
}
