#include "y/utest/driver.hpp"

Y_UTEST_DECL(128)
{

    Y_UTEST(root_zfind);
    Y_UTEST(tao_1);

    Y_UTEST(opt_parabolic);
    Y_UTEST(opt_minimize);
    
    Y_UTEST(algebra_lu);
}
Y_UTEST_EXEC()
