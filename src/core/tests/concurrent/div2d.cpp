
#include "y/concurrent/divide/2d.hpp"
#include "y/utest/run.hpp"

#include "y/container/sequence/vector.hpp"

using namespace Yttrium;




Y_UTEST(concurrent_div2d)
{
    typedef V2D<int> v2d;
    {
        Concurrent::Divide::Box<v2d> box( v2d(1,1), v2d(8,5) );

        for(size_t nproc=1;nproc<=8;++nproc)
        {
            std::cerr << std::endl << "nproc=" << nproc << std::endl;
            for(size_t i=1;i<=nproc;++i)
            {
                Concurrent::Divide::Tile2D<int> tile(nproc,i-1,box);
                std::cerr << "\t| tile[" << i << "] | = " << tile.h << std::endl;
                for(int j=1;j<=tile.h;++j)
                {
                    std::cerr << "\t\t" << tile[j] << std::endl;
                }
            }

            {
                Concurrent::Divide::Tiles2D<int> tiles(nproc);
                std::cerr << "tiles=" << tiles.content() << std::endl;
                tiles.remap(box);
                std::cerr << "tiles=" << tiles.content() << std::endl;

            }
        }
    }

    (std::cerr << "Extensive Test..." << std::endl).flush();
    {
        for(int x=1;x<=20;++x)
        {
            for(int y=1;y<=20;++y)
            {
                Concurrent::Divide::Box<v2d> box( v2d(1,1), v2d(x,y) );

                for(unsigned nproc=1;nproc<=8;++nproc)
                {
                    std::cerr << "nproc=" << nproc << " @ " << x << " x " << y << std::endl;
                    Concurrent::Divide::Tiles2D<int> tiles(nproc,box);
                    Vector<v2d> vertices;
                    for(unsigned i=1;i<=nproc;++i)
                    {
                        const Concurrent::Divide::Tile2D<int> &tile = tiles[i];
                        std::cerr << "\t" << tile << std::endl;
                        for(int j=tile.h;j>0;--j)
                        {
                            const Concurrent::Divide::HSegment<int> s = tile[j];
                            v2d v = s.start;
                            for(int k=s.width;k>0;--k,++v.x)
                            {
                                Y_ASSERT( box.includes(v) );
                                for(size_t l=vertices.size();l>0;--l)
                                {
                                    if( v == vertices[l] )
                                    {
                                        std::cerr << "multiple " << v << " / " << vertices[l] << std::endl;
                                        throw Exception("bad @x=%d, y=%d",x,y);
                                    }
                                }
                                vertices << v;
                            }
                        }
                    }
                }
            }
        }
    }



}
Y_UDONE()
