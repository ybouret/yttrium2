
#include "y/chemical/plexus/solve1d.hpp"
#include "y/mkl/root/zrid.hpp"
#include "y/mkl/api/almost-equal.hpp"

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
                size_t           & n;

                inline xreal_t operator()(const xreal_t xi)
                {
                    ++n;
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
            calls(0),
            xmul(),
            xadd(),
            zero(),
            one(1)
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

                ZeroFunction F  = { E, K, C, L, xmul, calls };
                XTriplet     xx = { zero, zero, zero };
                XTriplet     ff = { F(xx.a), zero, zero };

                switch( Sign::Of(ff.a) )
                {
                    case __Zero__: return 0;
                    case Positive:
                        //std::cerr << "need to forward" << std::endl;
                        switch(E.flow)
                        {
                            case Dangling: throw Specific::Exception(CallSign,"no components for '%s'", E.name.c_str());
                            case BothWays:
                            case ReacOnly:
                                xx.c = E.reac.fastLimit(C,L);
                                xmul.ld1(); E.prod.massAction(xmul,C,L,xx.c);
                                ff.c = -xmul.product(); // no more reactants
                                break;

                            case ProdOnly: {
                                assert(E.drNu>0);
                                const xreal_t dxi = K.pow(one / (xreal_t) (real_t)E.drNu );
                                while( (ff.c = F( xx.c += dxi )) >= zero )
                                    ;
                            } break;
                        }
                        break;

                    case Negative:
                        //std::cerr << "need to reverse" << std::endl;
                        switch(E.flow)
                        {
                            case Dangling: throw Specific::Exception(CallSign,"no components for '%s'", E.name.c_str());
                            case BothWays:
                            case ProdOnly:
                                xx.c = -E.prod.fastLimit(C,L);
                                xmul = K; E.reac.massAction(xmul,C,L,-xx.c);
                                ff.c = xmul.product(); // no more products
                                break;

                            case ReacOnly:
                                assert(E.drNu<0);
                                const xreal_t dxi = -K.pow(one / (real_t) (E.drNu) );
                                while( (ff.c = F( xx.c += dxi )) <= zero )
                                    ;
                                break;
                        }
                        break;
                }

                //std::cerr << "xx=" << xx << std::endl;
                //std::cerr << "ff=" << ff << std::endl;

                const xreal_t xi = solve(F,xx,ff);
                E.moveSafely(C,L,xi);
                //std::cerr << "xi=" << xi << " -> ma=" << ff.b << " / " << E.massAction(xmul,K,C,L) << std::endl;
                {
                    const xreal_t ma = E.massAction(xmul,K,C,L);
                    done             = (__Zero__ == Sign::Of(ma));
                }
                return xi;
            }


            ZRid<xreal_t> solve;
            size_t        cycle;
            size_t        calls;
            XMul          xmul;
            XAdd          xadd;
            const xreal_t zero;
            const xreal_t one;
        private:
            Y_Disable_Copy_And_Assign(Code);

        };

        Solve1D:: ~Solve1D() noexcept
        {
            assert(code);
            Destroy(code);
        }

        Solve1D:: Solve1D() : code( new Code() ), xmul(code->xmul)
        {

        }

        xreal_t Solve1D:: operator()(const Components &E,
                                     const xreal_t     K,
                                     XWritable        &C,
                                     const Level       L,
                                     const XReadable  &C0)
        {


            code->cycle = 0;
            code->calls = 0;
            bool     done = false;
            xreal_t  xi   = code->run(E,K,C,L,done);
            
            if(!done)
                while(true)
                {
                    ++code->cycle;
                    const xreal_t newXi = code->run(E,K,C,L,done);
                    if(done)                  break; // 'exact'
                    if(newXi.abs()>=xi.abs()) break;
                    xi = newXi;
                    assert(!done);
                }

            if( Crucial == E.status(C,L) )
                throw Specific::Exception(E.name.c_str(),"invalid Solve1D");
            
            //std::cerr << "calls = " << code->calls << " in #cycle=" << code->cycle<< std::endl;
            return E.extent(code->xadd,C,L,C0);
        }
    }

}
