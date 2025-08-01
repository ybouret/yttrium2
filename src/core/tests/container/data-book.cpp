
#include "y/container/ordered/data-book.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/random/shuffle.hpp"

using namespace Yttrium;


Y_UTEST(ordered_data_book)
{
    Random::ParkMiller ran;
    DataPool dp;
    Vector<size_t> keys;

    {
        DataBook db(dp);

        {
            db.free();
            keys.free();
            keys.adjust( 3+ ran.leq<size_t>(10), 0);
            for(size_t i=keys.size();i>0;--i)
            {
                keys[i] = i;
            }
            Random::Shuffle::Cxx(ran,keys);
            std::cerr << "keys=" << keys << std::endl;
            for(size_t i=keys.size();i>0;--i)
            {
                Y_ASSERT(db.insert_(keys[i]));
                std::cerr << db << std::endl;
            }
        }
    }
}
Y_UDONE()
