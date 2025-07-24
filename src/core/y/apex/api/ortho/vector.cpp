
#include "y/apex/api/ortho/vector.hpp"
#include "y/container/algorithm/for-each.hpp"

namespace Yttrium
{
    namespace Apex
    {
        namespace Ortho
        {

            Vector:: Vector(const Metrics &metrics) :
            Object(),
            Metrics(metrics),
            VectorType(metrics.dimensions),
            ncof(0),
            nrm2(),
            next(0),
            prev(0)
            {
            }


            Vector:: ~Vector() noexcept
            {
            }

            Vector:: Vector(const Vector &v) :
            Object(),
            Metrics(v),
            VectorType(v),
            ncof(v.ncof),
            nrm2(v.nrm2),
            next(0),
            prev(0)
            {
            }

            void Vector:: ldz() noexcept
            {
                Coerce(ncof)=0;
                Coerce(nrm2).ldz();
                for(size_t i=dimensions;i>0;--i) Coerce( (*this)[i] ).ldz();
            }

            void Vector:: update()
            {
                try {

                    Coerce(nrm2).ldz();
                    Coerce(ncof) = 0;
                    size_t  p = 0;
                    size_t  n = 0;
                    apn     g = 0;
                    for(size_t i=dimensions;i>0;--i)
                    {
                        const apz &z = (*this)[i];
                        switch(z.s)
                        {
                            case Negative:
                                ++n;
                                ++Coerce(ncof);
                                break;

                            case Positive:
                                ++p;
                                ++Coerce(ncof);
                                break;

                            case __Zero__:
                                continue;
                        }

                        Coerce(nrm2) += z.n.sqr();
                        g = (g.bits()<=0) ? z.n : Natural::GCD(g,z.n);
                    }
                    

                }
                catch(...)
                {
                    ldz();
                    throw;
                }
            }



        }

    }

}
