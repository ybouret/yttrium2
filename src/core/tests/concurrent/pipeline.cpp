#include "y/concurrent/api/pipeline/alone.hpp"
#include "y/concurrent/api/pipeline/queue.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;


namespace
{
    class Something
    {
    public:

    private:
        Y_Disable_Copy_And_Assign(Something);
    };
}

Y_UTEST(concurrent_pipeline)
{
    Concurrent::Alone stQ;
    Concurrent::Queue mtQ(Concurrent::Site::Default);



}
Y_UDONE()
