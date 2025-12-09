
template <>
Optimizer<real_t>:: Optimizer() :
OptimizerCommon(),
alpha(),
beta(),
curv(),
step(),
aini(),
aend(),
atry(),
lu(),
p(0),
lam(0),
xadd(),
pmin(-(int)(Numeric<real_t>::DIG+1)),
pmax( Numeric<real_t>::MAX_10_EXP),
pini(pmin/2),
ffmt( new Field::Layout1D(pmin,pmax) ),
lambda("lambda",ffmt),
zero(0),
one(1)
{
    static const fcpu_t ten = 10;

    std::cerr << "pmin=" << pmin << "; pmax=" << pmax << " =>" << ffmt << std::endl;
    for(int i=pmin+1;i<=pmax;++i)
    {
        const fcpu_t j = (fcpu_t)i;
        const fcpu_t l = std::pow(ten,j);
        Coerce(lambda[i]) = l;
    }
}

template <>
Optimizer<real_t>:: ~Optimizer() noexcept
{

}

template <>
void Optimizer<real_t>:: prepare(const size_t dims, const size_t nvar)
{
    alpha.make(nvar,nvar);
    curv.make(nvar,nvar);
    step.adjust(nvar,zero);
    beta.adjust(nvar,zero);

    aini.adjust(dims,zero);
    aend.adjust(dims,zero);
    atry.adjust(dims,zero);

}

template <>
bool Optimizer<real_t>:: getStep(real_t &sigma)
{

    assert(p>=pmin);
    assert(p<=pmax);
    const size_t n = curv.rows;
    sigma = zero;

BUILD_CURV:
    {
        curv.assign(alpha);
        const real_t fac = one + lam;
        for(size_t i=n;i>0;--i)
            curv[i][i] *= fac;
        //std::cerr << "alam=" << curv << std::endl;
        if(!lu.build(curv))
        {
            if(p>=pmax) return false; //!< singular matrix
            lam = lambda[++p];
            goto BUILD_CURV;
        }
    }

    step.ld(beta);
    lu.solve(curv,step);
    sigma = Tao::Dot(xadd,beta,step);

    if(sigma<zero)
        goto BUILD_CURV;

    return true;
}


template <>
void Optimizer<real_t>:: setScan(const Readable<real_t>         &aorg,
                                 const AdjustableEngine<real_t> &S) noexcept
{
    aini.ld(aorg);
    aend.ld(zero);

    // scatter current step into a_end
    S.scatter(aend,step);
    //std::cerr << "\tscatter_step=" << aend << std::endl;

    for(size_t j=aorg.size();j>0;--j)
    {
        aend[j] += aini[j];
    }


}

template <>
void Optimizer<real_t>:: errors(Writable<real_t>               &aerr,
                                const Readable<bool>           &used,
                                const AdjustableEngine<real_t> &S)
{
    assert( used.size() == aerr.size() );

    const size_t active = S.active(used); if(active<=0) return;
    size_t       dof    = S.count();
    switch( Sign::Of(active,dof) )
    {
        case Negative:
            assert(active<dof);
            dof -= active;
            break;

        case __Zero__: assert(active==dof);
            atry.ld(zero);
            goto DONE; // interpolation

        case Positive: assert(active>dof);
            return; // undefined
    }

    assert( alpha.gotSameMetricsThan(S.alpha) );
    alpha.assign(S.alpha);
    if( !lu.build(alpha) )
    {
        throw Specific::Exception(CallSign,"unexpected singular covariance");
    }

    lu.inv(alpha,curv);

    std::cerr << "alpha = " << S.alpha << std::endl;
    std::cerr << "curv0 = " << curv    << std::endl;
    S.flatten(curv,used);
    std::cerr << "curv  = " << curv    << std::endl;


    {
        const real_t sig2 = S.D2 / (fcpu_t)dof;
        for(size_t i=curv.rows;i>0;--i)
        {
            const real_t err2 = sig2 * Fabs<real_t>::Of(curv[i][i]);
            atry[i] = Sqrt<real_t>::Of(err2);
        }
    }

DONE:
    S.scatter(aerr,atry);
    std::cerr << "aerr=" << aerr << std::endl;

}
