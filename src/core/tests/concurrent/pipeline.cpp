#include "y/concurrent/api/pipeline/alone.hpp"
#include "y/concurrent/api/pipeline/queue.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(concurrent_pipeline)
{
    Concurrent::Alone stQ;
    Concurrent::Queue mtQ(Concurrent::Site::Default);
    
}
Y_UDONE()
