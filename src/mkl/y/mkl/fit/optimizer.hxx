
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
pmin(-(Numeric<real_t>::DIG+1)),
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
        const fcpu_t l = std::pow(ten,i);
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
        //std::cerr << "p=" << p << "/lam=" << lam << std::endl;
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
    std::cerr << "\tscatter_step=" << aend << std::endl;

    for(size_t j=aorg.size();j>0;--j)
    {
        aend[j] += aini[j];
    }

    //std::cerr << "\taini = " << aini << std::endl;
    //std::cerr << "\taend = " << aend << std::endl;


}
