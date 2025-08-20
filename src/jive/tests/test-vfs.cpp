


#include "y/jive/vfs.hpp"
#include "y/utest/run.hpp"
#include "y/vfs/local/fs.hpp"

using namespace Yttrium;
using namespace Jive;

Y_UTEST(vfs)
{

    LocalFS & fs = LocalFS:: Instance();

    if( argc > 1 )
    {
        Matching matching  = argv[1];
        if(argc>2)
        {

            _VFS::Apply(fs,
                        argv[1],
                        argv[1],
                        Matching::Exactly,
                        VFS::Entry::Path,
                        _VFS::Display);
        }
    }


}
Y_UDONE()
