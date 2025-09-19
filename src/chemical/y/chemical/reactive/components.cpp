
#include "y/chemical/reactive/components.hpp"
#include "y/stream/output.hpp"
#include "y/string/format.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        const char * const Components:: Arrows   = "<=>";
        const char * const Components:: Prod     = "Prod";
        const char * const Components:: Reac     = "Reac";

        const char * Components:: HumanReadableStatus(const Status st) noexcept
        {
            switch( st )
            {
                    Y_Return_Named_Case(Running);
                    Y_Return_Named_Case(Blocked);
                    Y_Return_Named_Case(Crucial);
            }
            return Core::Unknown;
        }


        Components:: ~Components() noexcept
        {
        }

        int Components:: stoichiometry(const Species &sp) const noexcept
        {
            for(const Actor *a=reac->head;a;a=a->next) if( &sp == & a->sp) return - (int) a->nu;
            for(const Actor *a=prod->head;a;a=a->next) if( &sp == & a->sp) return   (int) a->nu;
            return 0;
        }


        std::ostream & Components:: print(std::ostream &os) const
        {
            return os << name << ':' << reac.name << Arrows << prod.name;
        }


        static inline void displayActor(std::ostream &os, const Actor * const a, const XReadable &C, const Level L)
        {

            os << " [" << a->sp.name << "]=" << a->sp(C,L).str();
        }

        std::ostream & Components:: displayCompact(std::ostream &os, const XReadable &C, const Level L) const
        {
            os << '{';
            for(const Actor *a=reac->head;a;a=a->next) displayActor(os,a,C,L);
            for(const Actor *a=prod->head;a;a=a->next) displayActor(os,a,C,L);
            os << ' ' << '}';
            return os;
        }


        std::ostream & operator<<(std::ostream &os, const Components &self)
        {
            return os << '@' << self.name << ':' << self.reac.name << self.Arrows << self.prod.name;
        }

        void Components:: p(const unsigned nu, const Species &sp)
        {
            checkpoint(name,"p");
            if(prod.got(sp)) throw Specific::Exception(name.c_str(),"multiple product '%s'", sp.name.c_str());
            if(reac.got(sp)) throw Specific::Exception(name.c_str(),"already reactant '%s'", sp.name.c_str());
            Coerce(prod).add(nu,sp);
            updateFlow();
            Coerce(drNu) += (unit_t)nu;
        }

        void Components:: r(const unsigned nu, const Species &sp)
        {
            checkpoint(name,"r");
            if(prod.got(sp)) throw Specific::Exception(name.c_str(),"already product '%s'", sp.name.c_str());
            if(reac.got(sp)) throw Specific::Exception(name.c_str(),"multiple reactant '%s'", sp.name.c_str());
            Coerce(reac).add(nu,sp);
            updateFlow();
            Coerce(drNu) -= (unit_t)nu;
        }


        void Components:: p(const Species &sp) { p(1,sp); }
        void Components:: r(const Species &sp) { r(1,sp); }

        void Components:: updateFlow() noexcept
        {
            Coerce(xdim) = (xreal_t) (real_t) ( prod->size + reac->size );
            if(reac->size<=0)
            {
                if(prod->size<=0)
                {
                    Coerce(flow) = Dangling;
                }
                else
                {
                    Coerce(flow) = ProdOnly;
                }

            }
            else
            {
                if(prod->size<=0)
                {
                    Coerce(flow) = ReacOnly;
                }
                else
                {
                    Coerce(flow) = BothWays;
                }
            }


        }

        bool Components:: neutral() const
        {
            apz z = 0;
            for(const Actor *a=reac->head;a;a=a->next) z -=  (int) a->nu * a->sp.z;
            for(const Actor *a=reac->head;a;a=a->next) z +=  (int) a->nu * a->sp.z;
            return __Zero__ == z.s;
        }

        xreal_t Components:: massAction(XMul &X, const xreal_t K, const XReadable &C, const Level L) const
        {
            assert(frozen());

            X.ld1(); prod.massAction(X,C,L);
            const xreal_t rhs = X.product();

            X = K;   reac.massAction(X,C,L);
            const xreal_t lhs = X.product();

            return lhs - rhs;
        }

        xreal_t Components:: massAction(XMul &X, const xreal_t K, const XReadable &C, const Level L, const real_t xi) const
        {
            assert(frozen());

            X.ld1(); prod.massAction(X,C,L,xi);
            const xreal_t rhs = X.product();

            X = K;   reac.massAction(X,C,L,-xi);
            const xreal_t lhs = X.product();

            return lhs - rhs;
        }

        void Components:: moveSafely(XWritable &C, const Level L, const xreal_t xi) const
        {
            assert(frozen());
            prod.moveSafely(C, L,  xi);
            reac.moveSafely(C, L, -xi);
        }



        xreal_t Components:: extent(XAdd &xadd, const XReadable &C, const Level L, const XReadable &C0) const
        {
            xadd.ldz();

            for(const Actor *p=prod->head;p;p=p->next)
            {
                const size_t  i = p->sp.indx[L];
                const xreal_t x = (C[i]-C0[i])/p->xn;
                xadd << x;
            }

            for(const Actor *r=reac->head;r;r=r->next)
            {
                const size_t  i = r->sp.indx[L];
                const xreal_t x = (C0[i]-C[i])/r->xn;
                xadd << x;
            }

            return xadd.sum() /  xdim;
        }


        bool Components:: got(const Species &sp) const noexcept
        {
            return reac.got(sp) || prod.got(sp);
        }

        Status Components:: status(const XReadable &C, const Level L) const noexcept
        {
            if( reac.degenerate(C,L) )
            {
                if(prod.degenerate(C,L))
                {
                    return Blocked;
                }
                else
                {
                    return Crucial;
                }
            }
            else
            {
                if(prod.degenerate(C,L))
                {
                    return Crucial;
                }
                else
                {
                    return Running;
                }
            }
        }


        xreal_t Components:: affinity(XAdd &xadd, const xreal_t K, const XReadable &C, const Level L ) const
        {
            xadd = K.log();
            for(const Actor *a=prod->head;a;a=a->next)
            {
                const xreal_t cc  = a->sp(C,L);
                const xreal_t lc  = -cc.log();
                for(unsigned n=a->nu;n>0;--n) xadd << lc;
            }

            for(const Actor *a=reac->head;a;a=a->next)
            {
                const xreal_t cc  = a->sp(C,L);
                const xreal_t lc  = cc.log();
                for(unsigned n=a->nu;n>0;--n) xadd << lc;
            }

            return xadd.sum();
        }

        void Components:: jacobian(XWritable       &J,
                                   const XReadable &C,
                                   const Level      L) const
        {
            for(const Actor *a=reac->head;a;a=a->next)
            {
                const Species &sp = a->sp;
                const size_t   sj = sp.indx[L];
                J[sj] = a->xn / C[sj];
            }

            for(const Actor *a=prod->head;a;a=a->next)
            {
                const Species &sp = a->sp;
                const size_t   sj = sp.indx[L];
                J[sj] = -a->xn / C[sj];
            }

        }


        void Components:: diffAction(XWritable       &dma,
                                     XMul            &X,
                                     const xreal_t    K,
                                     const XReadable &C,
                                     const Level      L,
                                     XWritable       &ma) const
        {
            prod.diffAction(dma,X,minusOne,C,L,ma);
            reac.diffAction(dma,X,K,       C,L,ma);
        }

        static inline void makeArrow(OutputStream &fp,
                                     const Vizible &src,
                                     const Vizible &tgt,
                                     const String &color,
                                     const unsigned nu)
        {
            src.to(&tgt,fp) << "[";
            if(nu>1)
            {
                const String label = Formatted::Get("%u",nu);
                Vizible::Label(fp,label) << ",fontcolor=" << color << ",";
            }
            fp << "color=" << color;
            Vizible::Endl(fp << "]");
        }

        OutputStream & Components:: viz(OutputStream &fp, const String &color) const
        {
            nodeName(fp) << "[";
            Label(fp,name) << ",color=" << color << ",fontcolor=" << color << ",shape=";

            switch(flow)
            {
                case Dangling: fp << "ellipse";      break;
                case BothWays: fp << "box";          break;
                case ProdOnly: fp << "trapezium";    break;
                case ReacOnly: fp << "invtrapezium"; break;
            }

            Endl(fp<<"]");

            for(const Actor *a=prod->head;a;a=a->next)
            {
                makeArrow(fp,*this,a->sp,color,a->nu);
            }
            for(const Actor *a=reac->head;a;a=a->next)
            {
                makeArrow(fp,a->sp,*this,color,a->nu);
            }

            return fp;
        }


    }

}

