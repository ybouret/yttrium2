#include "y/utest/run.hpp"
#include <cassert>
#include <cstring>

namespace Yttrium
{
    namespace UTest
    {
        size_t Display::Width = 64;

        void Display::Value(const char *const name, const size_t size)
        {
            assert( 0!=name );
            const size_t nameLength = strlen(name);
            std::cerr << name;
            for(size_t i=nameLength;i<Width;++i) std::cerr << ' ';
            std::cerr << " = " << size << std::endl;
        }


        void Display:: Result(const char * const name, const bool flag)
        {
            assert(0!=name);
            const size_t nameLength = strlen(name);
            std::cerr << '[' << ' ' << name;
            for(size_t i=nameLength;i<Width;++i) std::cerr << ' ';

            std::cerr << (flag? Core::Success : Core::Failure);

            std::cerr << ' ' << ']' << std::endl;
        }

    }
}
