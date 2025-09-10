
#include "y/container/ordered/data-book.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/random/shuffle.hpp"
#include "y/container/iter/tests.hpp"

using namespace Yttrium;



Y_UTEST(ordered_data_book)
{
    Random::ParkMiller ran;

    DataBook<>::PoolType dp;
    DataBook<>           db(dp);


    {
        Vector<size_t> keys;

        for(size_t iter=0;iter<10;++iter)
        {
            db.free();
            keys.adjust( 3+ ran.leq<size_t>(30), 0);
            //keys.adjust(3,0);
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

    {
        db.free();
        Vector<uint16_t> keys;
        for(size_t iter=0;iter<10;++iter)
        {
            const uint16_t u = ran.to<uint16_t>();
            keys << u;
            db.insert(u);
        }
        std::cerr << "keys= " << keys << std::endl;
        std::cerr << "book= " << db   << std::endl;
        db.printAs<uint16_t>(std::cerr << "dbAs= ") << std::endl;
        std::cerr << std::endl;
    }

    {
        db.free();
        const int a[] = { 1, 2, 3, 4, 5 };

        for(unsigned i=0;i<sizeof(a)/sizeof(a[0]);++i)
        {
            db += &a[i];
        }
        std::cerr << "addr=" << db << std::endl;

        Iter::Test::AllForward(db);
        db.printAs<int *>(std::cerr << "dbAs= ") << std::endl;

    }



}
Y_UDONE()
