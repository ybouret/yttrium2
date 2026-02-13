


//! \file

#ifndef Y_Container_Algo_Unique_Included
#define Y_Container_Algo_Unique_Included 1

#include "y/type/sign.hpp"
#include "y/memory/stealth.hpp"
#include <iomanip>

namespace Yttrium
{
    namespace Algo
    {
        template <typename ARRAY> inline
        bool AcceptUnique(ARRAY &arr, const size_t j)
        {
            for(size_t i=1;i<j;++i)
            {
                if( arr[i] == arr[j] ) return false;
            }
            return true; // all different
        }

        template <typename ARRAY> inline
        void RejectUnique(ARRAY &arr, const size_t j) noexcept
        {
            const size_t n = arr.size();
            for(size_t k=j+1;k<=n;++k)
                Memory::Stealth::Swap(arr[k],arr[k-1]);
        }

        template <typename ARRAY> inline
        ARRAY & Unique(ARRAY &arr)
        {
            const size_t n = arr.size(); if(n<=1) return arr;
            size_t       u = 1;
            size_t       m = 0;

            while(true)
            {
                if( AcceptUnique(arr,u) )
                {
                    if(u+m>=n)
                    {
                        while(arr.size()>u) arr.popTail();
                        return arr;
                    }
                    ++u;
                }
                else
                {
                    RejectUnique(arr,u);
                    --u;
                    ++m;
                }
            }


        }

    }

}
#endif // !Y_Container_Algo_Unique_Included

