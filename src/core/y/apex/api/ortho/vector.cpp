
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

            std::ostream & operator<<(std::ostream &os, const Vector &v)
            {
                const VectorType &self = v;
                os << self;
                os << " // |#" << v.ncof << "|^2=" << v.nrm2;
                return os;
            }


            void Vector:: update()
            {
                try {

                    VectorType &v = *this;
                    Coerce(nrm2).ldz();
                    Coerce(ncof) = 0;
                    size_t   p = 0;
                    size_t   n = 0;
                    apn      g = 0;
                    SignType s = __Zero__;
                    for(size_t i=dimensions;i>0;--i)
                    {
                        const apz &z = v[i];
                        switch(z.s)
                        {
                            case Negative:
                                ++n;
                                ++Coerce(ncof);
                                s = Negative;
                                break;

                            case Positive:
                                ++p;
                                ++Coerce(ncof);
                                s = Positive;
                                break;

                            case __Zero__:
                                continue;
                        }

                        Coerce(nrm2) += z.n.sqr();
                        g = (g.bits()<=0) ? z.n : Natural::GCD(g,z.n);
                    }

                    std::cerr << "#p="  << p << std::endl;
                    std::cerr << "#n="  << n << std::endl;
                    std::cerr << "s = " << s << std::endl;
                    std::cerr << "g = " << g << std::endl;

                    if(g.bits()>0)
                    {
                        for(size_t i=dimensions;i>0;--i)
                        {
                            apn & _ = Coerce(v[i].n);
                            if(_.bits()<=0) continue;
                            _ /= g;
                        }

                        Coerce(nrm2) /= g.sqr();
                    }
                    else
                    {
                        
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
