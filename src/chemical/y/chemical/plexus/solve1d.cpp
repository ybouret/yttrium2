
#include "y/chemical/plexus/solve1d.hpp"
#include "y/mkl/root/zrid.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        using namespace MKL;

        namespace
        {
            struct ZeroFunction
            {
                const Components & E;
                const xreal_t      K;
                const XReadable  & C;
                const Level        L;
                XMul             & X;

                inline xreal_t operator()(const xreal_t xi) const
                {
                    return E.massAction(X,K,C,L,xi);
                }

            };
        }

        const char * const Solve1D:: CallSign = "Solve1D";

        class Solve1D :: Code : public Object
        {
        public:
            inline explicit Code() :
            solve(),
            cycle(0),
            xmul(),
            xadd(),
            zero()
            {}

            inline virtual ~Code() noexcept {}

            inline xreal_t run(const Components &E,
                               const xreal_t     K,
                               XWritable        &C,
                               const Level       L,
                               bool             &done)
            {
                assert(!done);
                ++cycle;

                ZeroFunction F  = { E, K, C, L, xmul };
                XTriplet     xx = { zero, zero, zero };
                XTriplet     ff = { F(xx.a), zero, zero };

                switch( Sign::Of(ff.a) )
                {
                    case __Zero__: return 0;
                    case Positive:
                        std::cerr << "need to forward" << std::endl;
                        switch(E.flow)
                        {
                            case Dangling: throw Specific::Exception(CallSign,"no components for '%s'", E.name.c_str());
                            case BothWays:
                            case ReacOnly:
                                xx.c = E.reac.fastLimit(C,L);
                                ff.c = F(xx.c); assert(ff.c<zero);
                                break;

                            case ProdOnly:
                                std::cerr << "need to handle prodOnly" << std::endl;
                                exit(1);
                                break;
                        }
                        break;

                    case Negative:
                        std::cerr << "need to reverse" << std::endl;
                        switch(E.flow)
                        {
                            case Dangling: throw Specific::Exception(CallSign,"no components for '%s'", E.name.c_str());
                            case BothWays:
                            case ProdOnly:
                                xx.c = -E.prod.fastLimit(C,L);
                                ff.c = F(xx.c); assert(ff.c>zero);
                                break;

                            case ReacOnly:
                                std::cerr << "need to handle reacOnly" << std::endl;
                                exit(1);
                                break;
                        }
                        break;
                }

                std::cerr << "xx=" << xx << std::endl;
                std::cerr << "ff=" << ff << std::endl;

                const xreal_t xi = solve(F,xx,ff);
                E.moveSafely(C,L,xi);
                std::cerr << "xi=" << xi << " -> ma=" << ff.b << " / " << E.massAction(xmul,K,C,L) << std::endl;
                {
                    const xreal_t ma = E.massAction(xmul,K,C,L);
                    done             = (__Zero__ == Sign::Of(ma));
                }
                return xi;
            }

            inline xreal_t extent(const Components &E, const XReadable &C, const Level L, const XReadable &C0)
            {
                xadd.ldz();

                for(const Actor *p=E.prod->head;p;p=p->next)
                {
                    const size_t i = p->sp.indx[L];
                    xadd << (C[i]-C0[i])/p->xn;
                }

                for(const Actor *r=E.prod->head;r;r=r->next)
                {
                    const size_t i = r->sp.indx[L];
                    xadd << (C0[i]-C[i])/r->xn;
                }


                return xadd.sum() / E.xdim;
            }


            ZRid<xreal_t> solve;
            size_t        cycle;
            XMul          xmul;
            XAdd          xadd;
            const xreal_t zero;

        private:
            Y_Disable_Copy_And_Assign(Code);

        };

        Solve1D:: ~Solve1D() noexcept
        {
            assert(code);
            Destroy(code);
        }

        Solve1D:: Solve1D() : code( new Code() )
        {

        }

        xreal_t Solve1D:: operator()(const Components &E,
                                     const xreal_t     K,
                                     XWritable        &C,
                                     const Level       L,
                                     const XReadable  &C0)
        {


            code->cycle = 0;
            bool     done = false;
            xreal_t  xi   = code->run(E,K,C,L,done);
            
            if(!done)
                while(true)
                {
                    ++code->cycle;
                    const xreal_t newXi = code->run(E,K,C,L,done);
                    if(done)                  break;
                    if(newXi.abs()>=xi.abs()) break;
                    xi = newXi;
                    assert(!done);
                }

            return code->extent(E,C,L,C0);
        }
    }

}
