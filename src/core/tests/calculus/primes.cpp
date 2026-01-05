
#include "y/calculus/prime/next.hpp"

#include "y/utest/run.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/stream/libc/output.hpp"
#include "y/calculus/bits-for.hpp"
#include "y/format/hexadecimal.hpp"

using namespace Yttrium;

template <typename T> static inline
T Transform(const T &x)
{
    return x;
}

Y_UTEST(calculus_primes)
{

    uint32_t i    = 3;

    Vector<uint8_t> gap;
    while(true)
    {
        const uint32_t j   = Prime::Next(i+1);
        const uint32_t g   = j-i;    Y_ASSERT( 0 == (g&1)  );
        const uint32_t d   = (g>>1); Y_ASSERT(d<256);
        gap << (uint8_t)d;
        i = j;
        if( j >= IntegerFor<uint16_t>::Maximum )
            break;
    }
    std::cerr << "#gap=" << gap.size() << std::endl;

    i = 3; Y_ASSERT(Prime::Test(i));
    for(size_t k=1;k<=gap.size();++k)
    {
        i += gap[k] << 1; std::cerr << i << std::endl;
        Y_ASSERT(Prime::Test(i));
    }


}
Y_UDONE()


#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/divide/1d.hpp"

#include "y/string/format.hpp"
#include "y/stream/libc/output.hpp"
#include "y/stream/libc/input.hpp"
#include <cstring>

namespace
{
    class Computer
    {
    public:
        static const uint64_t One   = 1;
        static const uint64_t Lower = 2;
        static const uint64_t Upper = One << 32;


        explicit Computer(const uint64_t nmax) noexcept :
        lower(Lower),
        upper(nmax<Lower ? Upper : nmax),
        delta(upper-lower+One)
        {

        }

        virtual ~Computer() noexcept
        {

        }

        static inline void Emit(OutputStream &fp, const uint64_t p)
        {
            fp << Hexadecimal(p,Concise).c_str() + 2<< "\n";
        }



#if defined(_MSC_VER)
#pragma warning ( disable : 4996 )
#endif

        inline void find(const Concurrent::Context &ctx)
        {
            const Concurrent::Divide::Tile1D<uint64_t> tile(ctx,delta,Lower);

            const uint64_t last = tile.utmost;
            { Y_Giant_Lock(); std::cerr << "@" << ctx << " : zone=" << tile << " -> "<< last << std::endl; }

            char fn[256];
            memset(fn,0,sizeof(fn));
            strncat(fn,"primes",sizeof(fn)-1);
            strncat(fn,ctx.c_str(),sizeof(fn)-1);
            strncat(fn,".txt",sizeof(fn)-1);


            OutputFile   fp(fn);

            uint64_t i=Prime::Next(tile.offset);
            while(i<=last)
            {
                Emit(fp,i);
                i = Prime::Next(++i);
            }
            assert(i>last);
            if(ctx.indx>=ctx.size)
            {
                Emit(fp,i);
            }
            { Y_Giant_Lock(); std::cerr << "@" << ctx << " : done" << std::endl; }

        }

        const uint64_t lower;
        const uint64_t upper;
        const uint64_t delta;

    private:
        Y_Disable_Copy_And_Assign(Computer);
    };

    const uint64_t Computer::Lower;

}

#include "y/system/wall-time.hpp"
#include "y/format/human-readable.hpp"
#include "y/vfs/local/fs.hpp"
#include "y/stream/libc/file/copy.hpp"
#include "y/string/env/convert.hpp"
#include "y/ascii/convert.hpp"
#include "y/hashing/sha1.hpp"
#include "y/hashing/md.hpp"

Y_UTEST(calculus_primes33)
{
    VFS &            fs = LocalFS::Instance();
    Concurrent::Crew crew( Concurrent::Site::Default );
    const uint64_t   nmax = EnvironmentConvert::To<uint64_t>("NMAX",0);
    Computer         computer(nmax);


    std::cerr << Hexadecimal(computer.lower) << " -> " << Hexadecimal(computer.upper) << std::endl;

    System::WallTime chrono;
    const uint64_t   mark = chrono.Ticks();
    {
        Concurrent::Kernel kernel( &computer, & Computer::find);
        crew(kernel);
    }
    const uint64_t ellapsed = chrono.Ticks() - mark;
    std::cerr << "Done in " << chrono(ellapsed) << " seconds" << std::endl;
    std::cerr << "Wait while merging files..." << std::endl;

    const String fileName = "primes33.txt";
    Hashing::SHA1 H;
    H.set();

    {
        OutputFile  fp(fileName);
        for(size_t rank=0;rank<crew.size();++rank)
        {
            const Concurrent::Member m(crew.size(),rank);
            const String fn = String("primes") + m.c_str() + ".txt";
            std::cerr << "[+] " << fn << std::endl;
            Libc::FileCopy::Merge(fp,fn,&H);
            fs.tryRemoveFile(fn);
        }
    }

    std::cerr << "Counting Lines..." << std::endl;
    {
        size_t count = 0;
        {
            String line;
            InputFile fp(fileName);
            while( fp.gets(line) )
                ++count;
        }
        std::cerr << "\t" << count << std::endl;
    }
    const Hashing::Digest D = Hashing::MD::Of(H);
    std::cerr << "\t" << H.callSign() << " = " << D << std::endl;

}
Y_UDONE()

#include "y/stream/gzip/input.hpp"

static inline
uint64_t Decode(const String &line)
{
    uint64_t     p = 0;
    const size_t n = line.size();
    for(size_t i=1;i<=n;++i)
    {
        p <<= 4;
        p |= Hexadecimal::ToDec(line[i]);
    }
    return p;
}

#include "y/calculus/prime/gap.hpp"

Y_UTEST(calculus_gap33)
{
    if(argc<=1) return 0;

    System::WallTime chrono;
    uint64_t         old64 = chrono.Ticks();

    uint64_t last = 0;
    {
        const String fn = argv[1];
        GZip::Input  inp(fn);
        OutputFile   out("hgaps33.txt");
        {
            String line;
            size_t count = 0;
            while( inp.gets(line) )
            {
                const uint64_t curr = Decode(line);
                ++count;
                switch(count)
                {
                    case 1:
                        Y_ASSERT(0==last);
                        Y_ASSERT(Prime::Gap::Lower == curr);
                        last = curr;
                        continue;

                    default:
                        Y_ASSERT(curr>last);
                        break;
                }
                const uint64_t g = curr - last;
                //std::cerr << "\tg=" << g << " (" << last << " -> " << curr << ")" << std::endl;
                Y_ASSERT( 0 == (g&1) );
                const uint64_t d = g>>1;
                out << Hexadecimal(d,Concise).c_str() + 2 << '\n';

                {
                    const uint64_t now64 = chrono.Ticks();
                    if( chrono( now64-old64) >= 1.0L )
                    {
                        old64 = now64;
                        (std::cerr << '.').flush();
                    }
                }

                last = curr;
            }
            std::cerr << "count=" << count << std::endl;
        }
    }

}
Y_UDONE()
