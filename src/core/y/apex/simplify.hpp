
//! \file

#ifndef Y_Apex_Simplify_Included
#define Y_Apex_Simplify_Included 1

#include "y/apex/integer.hpp"

namespace Yttrium
{
    namespace Apex
    {
        //______________________________________________________________________
        //
        //
        //
        //! Arithmetic simplifications
        //
        //
        //______________________________________________________________________
        struct Simplify
        {
            //! GCD of a range
            /**
             \param curr iterator
             \param size number of values
             \return gcd, zero means all zero
             */
            template <typename ITER> static inline
            Natural GCD(ITER curr, size_t size)
            {
                Natural g = 0;

                // first not zero
                while(size>0)
                {
                    const Natural &n = Get(*(curr++));
                    --size;
                    if(n.bits()) {
                        g = n;
                        break;
                    }
                }

                // update
                while(size-- > 0) {
                    const Natural &n = Get(*(curr++));
                    if(n.bits())
                        g = Natural::GCD(g,n);
                }

                return g;
            }


            //! GCD of a sequence
            /**
             \param seq sequence-like container
             \return gcd of all elements
             */
            template <typename SEQ> static inline
            Natural GCD(const SEQ &seq)
            {
                return GCD(seq.begin(),seq.size());
            }


            //! simplify sequence-like
            /**
             \param seq sequence, simplified
             \return gcd used to simplify
             */
            template <typename SEQ> static inline
            Natural Array(SEQ &seq)
            {
                const Natural g = GCD(seq);
                if(g.bits()>1)
                    Divide(seq,g);
                return g;
            }

            //! simplify sequence-like/denominator
            /**
             \param seq sequence, simplified
             \param denom denominator, simplified
             */
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

            //! simplify matrix
            /**
             \param M matrix, simplified
             \return gcd used to simplify
             */
            template <typename MATRIX> static inline
            Natural Apply(MATRIX &M)
            {
                typename MATRIX::ArrayType arr = M.asArray();
                return Array(arr);
            }

            //! simplify matrix/denominator
            /**
             \param M matrix, simplified
             \param denom denominator, simplified
             */
            template <typename MATRIX, typename DENOM> static inline
            void Apply(MATRIX &M, DENOM &denom)
            {
                typename MATRIX::ArrayType arr = M.asArray();
                return Array(arr,denom);
            }




        private:
            //! \param n natural \return mutable n
            static inline Natural & Get(const Natural &n) noexcept { return Coerce(n); }

            //! \param z integer \return mutable natural part
            static inline Natural & Get(const Integer &z) noexcept { return Coerce(z.n); }

            //! divide a range \param curr iterator \param size items \param g divider
            template <typename ITER> static inline
            void Divide(ITER curr, size_t size, const Natural &g)
            {
                assert(g>=2);
                while(size-- > 0 ) {
                    Natural & n = Get( *(curr++) );
                    if(n.bits()) n /= g;
                }
            }

            //! divide a sequence \param seq sequence-like \param g divider
            template <typename SEQ> static inline
            void Divide(SEQ &seq, const Natural &g)
            {
                Divide(seq.begin(),seq.size(),g);
            }

        };

    }
}

#endif
