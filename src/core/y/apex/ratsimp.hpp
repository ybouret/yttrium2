
//! \file

#ifndef Y_Apex_RatSimp_Included
#define Y_Apex_RatSimp_Included 1

#include "y/apex/simplify.hpp"
#include "y/apex/rational.hpp"

namespace Yttrium
{
    namespace Apex
    {
        //______________________________________________________________________
        //
        //
        //
        //! Rational Simplification
        //
        //
        //______________________________________________________________________
        struct RatSimp
        {

            //! \param iter iterator \param size number of rationals \return least common denominator
            template <typename ITER> static inline
            Natural LCD(ITER iter, size_t size)
            {
                if(size<=0) return 1;
                Natural res = (*iter).denom;
                for(--size;size>0;--size)
                {
                    ++iter;
                    res = Natural::LCM(res,(*iter).denom);
                }
                return res;
            }

            //! \param seq sequence \return least common denominator
            template <typename SEQ> static inline
            Natural LCD(SEQ &seq)
            {
                return LCD(seq.begin(),seq.size());
            }

            //! \param lcd factor \param iter iterator \param size number of rationals
            template <typename ITER> static inline
            void MulBy(const Natural &lcd, ITER iter, size_t size)
            {
                while(size-- > 0)
                {
                    apq & q = *iter; ++iter;
                    q *= lcd;
                    assert(1==q.denom);
                }
            }

            //! \param seq input/output reduced rationals \return solving factor
            template <typename SEQ> static inline
            Natural Array(SEQ &seq)
            {
                const Natural lcd = LCD(seq);
                MulBy(lcd,seq.begin(),seq.size());
                return lcd;
            }

        };

    }

}

#endif // !Y_Apex_RatSimp_Included

