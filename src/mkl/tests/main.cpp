#include "y/utest/driver.hpp"

Y_UTEST_DECL(128)
{

    Y_UTEST(interval);
    Y_UTEST(intervals);

    Y_UTEST(root_zfind);
    Y_UTEST(root_profile);

    Y_UTEST(tao_1);

    Y_UTEST(opt_parabolic);
    Y_UTEST(opt_minimize);
    
    Y_UTEST(algebra_lu);
    Y_UTEST(algebra_adjoint);
    Y_UTEST(algebra_ortho_space);
    Y_UTEST(algebra_coven);
    Y_UTEST(algebra_tridiag);
    Y_UTEST(algebra_cyclic);
    Y_UTEST(algebra_svd);
    Y_UTEST(algebra_eigen);

    Y_UTEST(interp_ratio);
    Y_UTEST(interp_poly);
    Y_UTEST(interp_cspline);

    Y_UTEST(drvs1D);
    Y_UTEST(drvsND);

    Y_UTEST(ode_rk4);
}
Y_UTEST_EXEC()
