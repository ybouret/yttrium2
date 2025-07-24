#include "y/apex/api/ortho/vector.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(apex_ortho_vector)
{

    
    Apex::Ortho::Metrics m = 5;
    Apex::Ortho::Vector  v(m);
    std::cerr << v << std::endl;

}
Y_UDONE()



