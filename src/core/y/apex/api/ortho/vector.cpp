
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


            Vector & Vector:: operator=( const Vector &v )
            {

                assert(dimensions==v.dimensions);
                try {
                    for(size_t i=dimensions;i>0;--i)
                    {
                        Coerce( (*this)[i] ) = v[i];
                    }
                    Coerce(nrm2) = v.nrm2;
                    Coerce(ncof) = v.ncof;
                }
                catch(...)
                {
                    ldz();
                    throw;
                }
                return *this;

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



                    const bool neg = (n>p) || ( (n<=p) && (Negative==s) );
#if 0
                    std::cerr
                    << " #p = " << p
                    << " #n = " << n
                    << " s = " << s
                    << " g = " << g
                    << " neg = " << neg << std::endl;
#endif
                    if(g.bits()>1)
                    {
                        if(neg)
                        {
                            for(size_t i=dimensions;i>0;--i)
                            {
                                const apz &z = v[i];
                                switch(z.s)
                                {
                                    case __Zero__: continue;
                                    case Positive: Coerce(z.n)/=g; Coerce(z.s) = Negative; continue;
                                    case Negative: Coerce(z.n)/=g; Coerce(z.s) = Positive; continue;
                                }
                            }
                        }
                        else
                        {
                            for(size_t i=dimensions;i>0;--i)
                            {
                                const apz &z = v[i];
                                switch(z.s)
                                {
                                    case __Zero__: continue;
                                    case Negative:
                                    case Positive:
                                        Coerce(z.n)/=g;
                                }
                            }
                        }

                        Coerce(nrm2) /= g.sqr();
                    }
                    else
                    {
                        assert(g<=1);
                        if(neg)
                        {
                            for(size_t i=dimensions;i>0;--i)
                                Sign::MakeOpposite(Coerce(v[i].s));;
                        }
                        // else do nothing
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
