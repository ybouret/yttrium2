

#include "y/static/workspace/solitary.hpp"
#include "y/type/destruct.hpp"
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

    class Anything : public Static::Solitary<Something>
    {
    public:
        explicit Anything() : Static::Solitary<Something>()
        {
            new (data) Something;
        }

        virtual ~Anything() noexcept
        {
            DestructAs<Something>(data);
        }
    private:
        Y_Disable_Copy_And_Assign(Anything);
    };


}

Y_UTEST(static_solitary)
{

    Anything any;


}
Y_UDONE()
