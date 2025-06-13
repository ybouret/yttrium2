
//! \file

#ifndef Y_Sorting_Index_Included
#define Y_Sorting_Index_Included 1

#include "y/type/sign.hpp"
#include "y/container/writable.hpp"

namespace Yttrium{

    namespace Sorting
    {

        struct Index
        {

            //______________________________________________________________________
            //
            //
            //! make index using 'SignType compare(lhs,rhs)'
            //
            //______________________________________________________________________
            template <typename T,typename FUNC> static inline
            void Make(Writable<size_t>  & idx,
                      FUNC              & cmp,
                      const Readable<T> & arr) noexcept
            {
                
                //------------------------------------------------------------------
                // initialize indices
                //------------------------------------------------------------------
                const size_t n = idx.size(); assert( arr.size() == idx.size() );
                for(size_t i=n;i>0;--i) idx[i] = i;
                
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
                    while( inc <= n );
                    do
                    {
                        inc /= 3;
                        for( size_t i=inc+1;i<=n;++i)
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
                
#if 0
                std::cerr << "idx:";
                for(unsigned i=1;i<=n;++i)
                {
                    std::cerr << " " << arr[ idx[i] ] << "@" << idx[i];
                }
                std::cerr << std::endl;
#endif
                
                assert( Check(idx,cmp,arr) );
            }
            
            //______________________________________________________________________
            //
            //! check that indexing is valid, mostly to debug
            //______________________________________________________________________
            template <typename T,typename FUNC> static inline
            bool Check(const Readable<size_t> &idx,
                       FUNC                   &cmp,
                       const Readable<T>      &arr)
            {
                const size_t n = idx.size(); assert( arr.size() == idx.size() );
                for(size_t i=1;i<n;++i) {
                    const size_t   ilo = idx[i];
                    const size_t   ihi = idx[i+1];
                    const SignType sgn = cmp( arr[ ilo ], arr[ ihi ]);
                    switch( sgn )
                    {
                        case __Zero__:
                        case Negative:
                            break;
                        case Positive:
                            return false;
                    }
                }
                return true;
            }
            
        };
    }

}

#endif

