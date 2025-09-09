
//! \file

#ifndef Y_Apex_Simplify_Included
#define Y_Apex_Simplify_Included 1

#include "y/apex/integer.hpp"

namespace Yttrium
{
    namespace Apex
    {

        struct Simplify
        {
            template <typename ITER> static inline
            Natural GCD(ITER curr, size_t size)
            {
                Natural g = 0;

                // first not zero
                while(size>0)
                {
                    const Natural &n = Get(*(curr++));
                    --size;
                    if(n.bits())
                    {
                        g = n;
                        break;
                    }
                }

                // update
                while(size-- > 0)
                {
                    const Natural &n = Get(*(curr++));
                    if(n.bits())
                    {
                        g = Natural::GCD(g,n);
                    }
                }

                return g;
            }



            template <typename SEQ> static inline
            Natural GCD(const SEQ &seq)
            {
                return GCD(seq.begin(),seq.size());
            }



            template <typename SEQ> static inline
            Natural Array(SEQ &seq)
            {
                const Natural g = GCD(seq);
                if(g.bits()>1)
                    Divide(seq,g);
                return g;
            }

            template <typename SEQ, typename DENOM> static inline
            void Array(SEQ &seq, DENOM &denom)
            {
                Natural &d = Get(denom); assert(d.bits()>0);
                Natural g  = GCD(seq);
                g = Natural::GCD(g,d);
                if(g.bits()>1)
                {
                    Divide(seq,g);
                    d /= g;
                }
            }

            template <typename MATRIX> static inline
            Natural Apply(MATRIX &M)
            {
                typename MATRIX::ArrayType arr = M.asArray();
                return Array(arr);
            }

            template <typename MATRIX, typename DENOM> static inline
            void Apply(MATRIX &M, DENOM &denom)
            {
                typename MATRIX::ArrayType arr = M.asArray();
                return Array(arr,denom);
            }




        private:
            static inline Natural & Get(const Natural &n) noexcept { return Coerce(n); }
            static inline Natural & Get(const Integer &z) noexcept { return Coerce(z.n); }

            template <typename ITER> static inline
            void Divide(ITER curr, size_t size, const Natural &g)
            {
                assert(g>=2);
                while(size-- > 0 ) {
                    Natural & n = Get( *(curr++) );
                    if(n.bits()) n /= g;
                }
            }

            template <typename SEQ> static inline
            void Divide(SEQ &seq, const Natural &g)
            {
                Divide(seq.begin(),seq.size(),g);
            }

        };

    }
}

#endif
