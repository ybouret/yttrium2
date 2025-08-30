
template <>
real_t Minimize<real_t>:: Run(const Minimizing::How how,
                              Triplet<real_t> & x,
                              Triplet<real_t> & f,
                              FunctionType &    F)
{
    switch(how)
    {
        case Minimizing::Direct:
            if(!f.isLocalMinimum())
                throw Specific::Exception(Minimizing::CallSign,"no local minimum to process directly");
            break;

        case Minimizing::Expand: throw Specific::Exception(Minimizing::CallSign,"not implemented");

        case Minimizing::Inside:
            if( Bracket<real_t>::Inside(x,f,F) )
                break;
            std::cerr << "Global Min @" << x.a << std::endl;
            f.b = f.c = f.a = F( x.b = x.c = x.a );
            return x.a;
    }

    assert(f.isLocalMinimum());
    return Optimize<real_t>::Run(x,f,F);
}


