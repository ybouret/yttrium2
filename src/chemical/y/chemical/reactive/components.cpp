
#include "y/chemical/reactive/components.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        const char * const Components:: Arrows   = "<=>";
        const char * const Components:: Prod     = "Prod";
        const char * const Components:: Reac     = "Reac";

        Components:: ~Components() noexcept
        {
        }

        std::ostream & operator<<(std::ostream &os, const Components &self)
        {
            return os << '@' << self.name << ':' << self.reac.name << self.Arrows << self.prod.name;
        }

        void Components:: p(const unsigned nu, const Species &sp)
        {
            checkpoint(name,"p");
            if(prod.has(sp)) throw Specific::Exception(name.c_str(),"multiple product '%s'", sp.name.c_str());
            if(reac.has(sp)) throw Specific::Exception(name.c_str(),"already reactant '%s'", sp.name.c_str());
            Coerce(prod).add(nu,sp);
            updateFlow();
            Coerce(drNu) += (unit_t)nu;
        }

        void Components:: r(const unsigned nu, const Species &sp)
        {
            checkpoint(name,"r");
            if(prod.has(sp)) throw Specific::Exception(name.c_str(),"already product '%s'", sp.name.c_str());
            if(reac.has(sp)) throw Specific::Exception(name.c_str(),"multiple reactant '%s'", sp.name.c_str());
            Coerce(reac).add(nu,sp);
            updateFlow();
            Coerce(drNu) -= (unit_t)nu;
        }


        void Components:: p(const Species &sp) { p(1,sp); }
        void Components:: r(const Species &sp) { r(1,sp); }

        void Components:: updateFlow() noexcept
        {
            Coerce(xdim) = xreal_t( prod->size + reac->size );
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


        bool Components:: has(const Species &sp) const noexcept
        {
            return reac.has(sp) || prod.has(sp);
        }


        bool Components:: linkedTo(const Components &other) const noexcept
        {
            for(const Actor *a=prod->head;a;a=a->next)
                if( other.has(a->sp) ) return true;

            for(const Actor *a=reac->head;a;a=a->next)
                if( other.has(a->sp) ) return true;

            return false;
        }
    }

}

