
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
#include "y/concurrent/split/1d.hpp"
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



        inline void find(const Concurrent::Context &ctx)
        {
            Concurrent::Split::In1D       in1d(delta);
            const Concurrent::Split::Zone zone = in1d(ctx,Lower);
            const uint64_t                last = (zone.offset + zone.length - One);
            { Y_Giant_Lock(); std::cerr << "@" << ctx << " : zone=" << zone << " -> "<< last << std::endl; }

            char fn[256];
            memset(fn,0,sizeof(fn));
            strncat(fn,"primes",sizeof(fn)-1);
            strncat(fn,ctx.c_str(),sizeof(fn)-1);
            strncat(fn,".txt",sizeof(fn)-1);


            OutputFile   fp(fn);

            uint64_t i=Prime::Next(zone.offset);
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
#include "y/string/env.hpp"
#include "y/ascii/convert.hpp"
#include "y/hashing/sha1.hpp"
#include "y/hashing/md.hpp"

Y_UTEST(calculus_primes33)
{
    VFS &            fs = LocalFS::Instance();
    Concurrent::Crew crew( Concurrent::Site::Default );
    String           nstr;
    uint64_t         nmax = 0;
    if( Environment::Get(nstr,"NMAX") )
    {
        nmax = ASCII::Convert::To<uint64_t>(nstr,"nmax");
    }
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

Y_UTEST(calculus_gap33)
{
    if(argc<=1) return 0;

    const String fn = argv[1];
    GZip::Input  fp(fn);
    {
        String line;
        size_t count = 0;
        while( fp.gets(line) )
        {
            std::cerr << Decode(line) << std::endl;
            ++count;
            if(count>=5) break;
        }
    }

}
Y_UDONE()
