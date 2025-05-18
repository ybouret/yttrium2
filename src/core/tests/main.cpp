#include <iostream>
#include "y/check/usual.hpp"

using namespace Yttrium;

int main()
{
    assert(  Good(0,0) || Die("Invalid Buffer") );
	return 0;
}
