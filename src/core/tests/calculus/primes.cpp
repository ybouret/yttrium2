
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
        gap << d;
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

namespace
{
    class Computer
    {
    public:
        static const uint64_t One   = 1;
        static const uint64_t Lower = 2;
        //static const uint64_t Upper = One << 32;


        explicit Computer(const uint64_t nmax) noexcept :
        lower(Lower),
        upper(nmax),
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

            ctx.sync.lock();
            const String fn = "primes" + ctx.name() + ".txt";
            ctx.sync.unlock();
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

Y_UTEST(calculus_primes33)
{
    VFS &            fs = LocalFS::Instance();
    Concurrent::Crew crew( Concurrent::Site::Default );
    Computer         computer(1000);

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
    {
        OutputFile fp(fileName);

        for(size_t rank=0;rank<crew.size();++rank)
        {
            const Concurrent::Member m(crew.size(),rank);
            const String fn = "primes" + m.name() + ".txt";
            std::cerr << "[+] " << fn << std::endl;
            Libc::FileCopy::Merge(fp,fn);
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
    
}
Y_UDONE()
