#include "y/concurrent/data/inventory.hpp"
#include "y/protean/proto/list.hpp"
#include "y/utest/run.hpp"
#include "y/container.hpp"
#include "y/threading/multi-threaded-object.hpp"

using namespace Yttrium;

namespace
{

#if 0
    class Char
    {
    public:
        Y_Args_Declare_Spec(uint8_t,Type);
        static const char * const               CallSign;
        static const  System::AtExit::Longevity LifeTime = 1000;


        Char(ParamType c) noexcept :
        next(0), prev(0), data(c)
        {
        }

        ~Char() noexcept {}

        Char(const Char &ch) noexcept : next(0), prev(0), data(ch.data)
        {
        }

        inline Type      & operator*() noexcept { return data; }
        inline ConstType & operator*() const noexcept { return data; }

        Char *next;
        Char *prev;

    private:
        Y_Disable_Assign(Char);
        uint8_t data;
    };

    const char * const Char:: CallSign = "Chars";


    typedef Protean::WarpedCacheOf<Char,MultiThreadedHandle> CharCache;

    typedef Protean::ListProto<Char, CharCache &, Container,MultiThreadedObject> CharsProto;

    class Chars : public CharsProto
    {
    public:
        explicit Chars() : CharsProto( Concurrent::Inventory<Char>::Instance() )
        {
        }

        virtual ~Chars() noexcept
        {
        }

        Chars(const Chars &other) : CharsProto( other.pool )
        {
            duplicate(other);
        }


        Chars & operator=(const Chars &other)
        {
            Chars temp(other);
            list.swapListFor(temp.list);
            return *this;
        }

    };
#endif




    class Dummy
    {
    public:
        static const System::AtExit::Longevity LifeTime = 007;
        static const char * const              CallSign;
        typedef const int ParamType;

        Dummy() noexcept : value(0)
        {
        }

        ~Dummy() noexcept
        {
        }

        Dummy(const Dummy &other) : value(other.value) {}

        
        const int value;


    private:
        Y_Disable_Assign(Dummy);
    };
    const char * const Dummy:: CallSign = "Dummy";



}

Y_UTEST(concurrent_inventory)
{
    Concurrent::Singulet::Verbose = true;
    Concurrent::Inventory<Dummy> & inventory = Concurrent::Inventory<Dummy>::Instance();
    inventory.display(std::cerr,1);

#if 0
    Chars chars;
    chars << 'a' >> 'b';
    std::cerr << chars << std::endl;
    Chars ccopy(chars);
    Chars copy2;
    copy2 = ccopy;
    std::cerr << copy2 << std::endl;
#endif
    
}
Y_UDONE()

