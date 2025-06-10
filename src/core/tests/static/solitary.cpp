

#include "y/static/workspace/solitary.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace  {

    class Something
    {
    public:
        Something()
        {
        }

        ~Something() noexcept
        {
        }


    private:
        Y_Disable_Copy_And_Assign(Something);
    };

}

Y_UTEST(static_solitary)
{

    Static::Solitary<Something> sole;


}
Y_UDONE()
