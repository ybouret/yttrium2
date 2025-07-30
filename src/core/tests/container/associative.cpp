
#include "y/container/iter/tests.hpp"

#include "y/container/associative/hash/set.hpp"
#include "y/container/associative/hash/map.hpp"


#include "y/container/associative/suffix/set.hpp"
#include "y/container/associative/suffix/map.hpp"
#include "y/container/sequence/vector.hpp"


#include "y/utest/run.hpp"

#include "y/string.hpp"
#include "y/pointer/arc.hpp"
#include "y/pointer/keyed.hpp"

#include "y/stream/libc/input.hpp"
#include "y/random/park-miller.hpp"
#include "y/random/shuffle.hpp"

using namespace Yttrium;

namespace
{
    template <typename ASSOC>
    static inline void testAssoc(ASSOC                  &db,
                                 const Readable<String> &keys)
    {
        const ASSOC &cdb = db;
        for(size_t i=keys.size();i>0;--i)
        {
            Y_ASSERT( cdb.search( keys[i] ) );
            Y_ASSERT( db.search( keys[i] ) );
        }

        Iter::Test::AllForward(db);

        std::cerr << db << std::endl;

        {
            const ASSOC cpy(db);
            Y_ASSERT(cpy.size()==db.size());
        }

    }

}

Y_UTEST(container_associative)
{

    Random::ParkMiller ran;

    typedef SuffixSet<String,String> SfxSet;
    typedef HashSet<String,String>   HshSet;

    typedef SuffixMap<String,String> SfxMap;
    typedef HashMap<String,String>   HshMap;


    SfxSet         sfxSet;
    HshSet         hshSet;
    SfxMap         sfxMap;
    HshMap         hshMap;
    Vector<String> keys;

    if(argc>1)
    {
        InputFile fp(argv[1]);
        String    key;
        while(fp.gets(key))
        {
            if( !sfxSet.insert(key) ) continue;
            keys << key;
            Y_ASSERT(hshSet.insert(key));
            Y_ASSERT(sfxMap.insert(key,key));
            Y_ASSERT(hshMap.insert(key,key));
        }
    }

    Random::Shuffle::Cxx(ran,keys);
    std::cerr << keys << std::endl;

    testAssoc(sfxSet,keys);
    testAssoc(hshSet,keys);
    testAssoc(sfxMap,keys);

    



}
Y_UDONE()
