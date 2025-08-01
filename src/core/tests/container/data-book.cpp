
#include "y/container/ordered/data-book.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/random/shuffle.hpp"

using namespace Yttrium;


Y_UTEST(ordered_data_book)
{
    Random::ParkMiller ran;
    DataPool           dp;

    {
        DataBook db(dp);
        Vector<size_t> keys;

        for(size_t iter=0;iter<10;++iter)
        {
            db.free();
            keys.adjust( 3+ ran.leq<size_t>(10), 0);
            std::cerr << db << std::endl;
            for(size_t i=keys.size();i>0;--i)
            {
                keys[i] = i;
            }
            Random::Shuffle::Cxx(ran,keys);
            for(size_t i=keys.size();i>0;--i)
            {
                Y_ASSERT(db.insert(keys[i]));
                std::cerr << db << std::endl;
            }
            Random::Shuffle::Cxx(ran,keys);
            for(size_t i=keys.size();i>0;--i)
            {
                Y_ASSERT(db.remove(keys[i]));
                std::cerr << db << std::endl;
            }

        }
    }
}
Y_UDONE()
