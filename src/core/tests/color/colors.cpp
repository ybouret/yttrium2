#include "y/color/rgb.hpp"
#include "y/color/rgba.hpp"

#include "y/utest/run.hpp"
#include "y/format/hexadecimal.hpp"

using namespace Yttrium;

Y_UTEST(colors)
{
    std::cerr << Color::Privy::OpaqueFP<float>       ::Value << std::endl;
    std::cerr << Color::Privy::OpaqueFP<double>      ::Value << std::endl;
    std::cerr << Color::Privy::OpaqueFP<long double> ::Value << std::endl;

    std::cerr << (unsigned)Color::Privy::OpaqueIP<uint8_t> ::Value<< std::endl;
    std::cerr << Color::Privy::OpaqueIP<uint16_t> ::Value << std::endl;
    std::cerr << Color::Privy::OpaqueIP<uint32_t> ::Value << std::endl;
}
Y_UDONE()

