//#include "y/mkl/algebra/cyclic.hpp"
#include "y/utest/run.hpp"
#include "y/mkl/v2d.hpp"
#include "y/container/cxx/array.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace MKL
    {
#if 0
        template <typename T>
        class CyclicSpline : public Writable< V2D<T> >
        {
        public:
            typedef V2D<T> Vertex;

            explicit CyclicSpline(const size_t n);
            virtual ~CyclicSpline() noexcept;

            void update();


            virtual const char * callSign() const noexcept { return "CyclicSpline"; }
            virtual size_t       size() const throw() { return code->N; }

            const V2D<T> & operator[](const size_t i) const noexcept
            {
                return code->P[i];
            }

            V2D<T> & operator[](const size_t i)   noexcept
            {
                return code->P[i];
            }

            const Readable< V2D<T> > & accel() const noexcept
            {
                return code->d2P;
            }

            V2D<T> operator()(const T t) const noexcept
            {
                return code->eval(t,0,0);
            }

            V2D<T> operator()(const T t, V2D<T> &v) const noexcept
            {
                return code->eval(t,&v,0);
            }

            V2D<T> operator()(const T t, V2D<T> &v, V2D<T> &a) const noexcept
            {
                return code->eval(t,&v,&a);
            }

        private:
            class Code;
            Code *code;
            Y_DISABLE_COPY_AND_ASSIGN(CyclicSpline);
        };



        template <typename T>
        class CyclicSpline<T>::Code : public Object
        {
        public:
            typedef Memory::Dyadic         Model;
            typedef CxxArray<Vertex,Model> Vertices;
            typedef CxxArray<T,Model>      Tableau;

            inline explicit Code(const size_t n) :
            Object(),
            N(n),
            lim(N),
            Nm1(N-1),
            zero(0),
            one(1),
            six(6),
            P(n),
            d2P(n),
            rhs(n),
            cof(n),
            mu(n)
            {
                for(size_t i=N;i>0;--i)
                {
                    mu.b[i] = 4;
                    mu.a[i] = mu.c[i] = 1;
                }

                std::cerr << "mu=" << mu << std::endl;
            }

            inline virtual ~Code() noexcept {}

            static inline T Compute(const Vertex &prev,
                                    const Vertex &curr,
                                    const Vertex &next,
                                    const size_t  dim) noexcept
            {
                const T mid = curr[dim];
                const T res = (prev[dim]-mid) + (next[dim]-mid);
                return res;
            }

            inline void update()
            {
                std::cerr << "cspline: interp #" << N << std::endl;
                for(size_t dim=1;dim<=2;++dim)
                {
                    rhs[1] = six * Compute(P[N],P[1],P[2],dim);
                    for(size_t i=Nm1;i>1;--i)
                    {
                        rhs[i] = six * Compute(P[i-1],P[i],P[i+1],dim);
                    }
                    rhs[N] = six * Compute(P[Nm1],P[N],P[1],dim);

                    //std::cerr << "dim=" << dim << " : rhs=" << rhs << std::endl;
                    mu.solve(cof,rhs);
                    for(size_t i=N;i>0;--i)
                    {
                        d2P[i][dim] = cof[i];
                    }
                }
            }

            inline V2D<T> eval(T t, V2D<T> *speed, V2D<T> *accel) const
            {

                while(t>lim)  t -= lim;
                while(t<zero) t += lim;
                const T       ta = Floor<T>::Of(t);
                size_t        ia = static_cast<size_t>(ta); if(++ia>N) ia=1;
                size_t        ib = ia;                      if(++ib>N) ib=1;
                const T B = Clamp(zero,t-ta,one);
                const T A = one-B;
                const T B2 = B*B;
                const T A2 = A*A;
                const T D  = B*(B2-one)/six;
                const T C  = A*(A2-one)/six;
                const V2D<T> &Pa = P[ia];
                const V2D<T> &Pb = P[ib];
                const V2D<T> &d2Pa = d2P[ia];
                const V2D<T> &d2Pb = d2P[ib];
                if(0!=speed)
                {
                    *speed = (Pb-Pa) - (3*A2-one)/six * d2Pa + (3*B2-one)/six * d2Pb;
                }
                if(0!=accel)
                {
                    *accel = A*d2Pa + B * d2Pb;
                }
                return A*Pa + B*Pb + C * d2Pa + D * d2Pb;;
            }





            const size_t N;    //!< number of points
            const T      lim;  //!< N as T
            const size_t Nm1;  //!< N-1
            const T      zero; //!< 0
            const T      one;  //!< 1
            const T      six;  //!< 6
            Vertices     P;
            Vertices     d2P;
            Tableau      rhs;
            Tableau      cof;
            Cyclic<T>    mu;

        private:
            Y_DISABLE_COPY_AND_ASSIGN(Code);
        };

        template <typename T>
        CyclicSpline<T>:: CyclicSpline(const size_t n) : code( new Code(n) )
        {
        }

        template <typename T>
        CyclicSpline<T>:: ~CyclicSpline() noexcept
        {
            assert(0!=code);
            Nullify(code);
        }

        template <typename T>
        void CyclicSpline<T>:: update()
        {
            assert(0!=code);
            code->update();
        }
#endif

    }
}


using namespace Yttrium;


#include "y/stream/libc/output.hpp"
#include "y/random/bits.hpp"
#include "y/mkl/numeric.hpp"

Y_UTEST(interp_cspline)
{

#if 0
    Random::Rand              ran;
    MKL::CyclicSpline<double> S(3);

    const double theta0 = 0;
    const double theta1 = 2*MKL::Numeric<double>::PI/3;
    const double theta2 = 4*MKL::Numeric<double>::PI/3;
    S[1] = V2D<double>(cos(theta0),sin(theta0));
    S[2] = V2D<double>(cos(theta1),sin(theta1));
    S[3] = V2D<double>(cos(theta2),sin(theta2));

    S.update();
    std::cerr << "S=" << S << std::endl;
    std::cerr << "accel=" << S.accel() << std::endl;
    {
        OutputFile fp("csdata.dat");
        for(size_t i=1;i<=S.size();++i)
        {
            fp("%g %g\n", S[i].x, S[i].y);
        }
        fp("%g %g\n", S[1].x, S[1].y);
    }

    {
        OutputFile fp("cspline.dat");
        for(double i=-10;i<=10;i+= 0.1 * ran.to<double>() )
        {
            V2D<double>       v;
            V2D<double>       a;
            const V2D<double> r = S(i,v,a);
            const double      speed = v.norm();
            const V2D<double> tv = v/speed;
            const V2D<double> nv = tv.ortho();
            const double      H  = (v.x*a.y-a.x*v.y)/(speed*speed*speed);
            const V2D<double> q = r + 0.1 * (1.0/H) * nv;
            fp("%g %g %g %g\n", r.x, r.y, q.x, q.y);
        }
    }
#endif

}
Y_UDONE()



