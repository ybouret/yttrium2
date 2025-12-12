
#include "y/container/sequence/vector.hpp"
#include "y/random/park-miller.hpp"
#include "y/random/shuffle.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(sequence_vector)
{
    Vector<size_t>     v;
    Random::ParkMiller ran;

    std::cerr << v << std::endl;

    for(size_t i=0;i<20;++i)
    {
        v.pushTail(i);
        std::cerr << v << std::endl;
    }

    v.release();
    for(size_t i=0;i<20;++i)
    {
        v.pushHead(i);
        std::cerr << v << std::endl;
    }
    std::cerr << v[1] << std::endl;
    v.free();
    std::cerr << v << std::endl;

    for(size_t i=0;i<20;++i)
    {
        v.pushHead(i);
        std::cerr << v << std::endl;
    }

    while(v.size())
    {
        v.moveAtTail( ran.in<size_t>(1,v.size()));
        v.popTail();
        std::cerr << v << std::endl;
    }


    Vector<int> w;
    for(size_t i=10;i<=20;++i)
    {
        v.pushHead(i);
        w.pushTail(ran.in<int>(10,20));
        //std::cerr << v << std::endl;
    }

    std::cerr << std::endl;
    std::cerr << "hsort" << std::endl;
    Random::Shuffle::Cxx(ran,v);
    std::cerr << v << std::endl;
    v.hsort(Sign::Increasing<size_t>);
    std::cerr << v << std::endl;
    std::cerr << std::endl;
    std::cerr << "co-hsort" << std::endl;
    Random::Shuffle::Cxx(ran,v);
    std::cerr << v << std::endl;
    std::cerr << w << std::endl;
    v.hsort(Sign::Increasing<size_t>,w);
    std::cerr << v << std::endl;
    std::cerr << w << std::endl;


}
Y_UDONE()

