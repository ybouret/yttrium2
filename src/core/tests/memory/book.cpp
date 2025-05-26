

#include "y/memory/object/book.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"

#include <cstring>

using namespace Yttrium;

namespace
{

}

Y_UTEST(memory_book)
{
    Concurrent::Singulet::Verbose = true;
    System::Rand  ran;


    Memory::Book & book = Memory::Book::Instance();
    std::cerr << "ready for " << book.callSign() << std::endl;

    for(size_t i=10+ran.leq(10);i>0;--i)
    {
        book.cache( unsigned(Memory::Book::MinPageShift + ran.leq(Memory::Book::NumPageShift/5)), ran.leq(5));
    }

    book.display(std::cerr);
    

}
Y_UDONE()
