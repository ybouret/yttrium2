#include "ionocell.hpp"

IonoCell:: ~IonoCell() noexcept
{
}

const char * const IonoCell:: CallSign = "IonoCell";

IonoCell:: IonoCell() : Soak<IonoCell>(),
weasel( Weasel::Instance() ),
lib(),
eqs()
{
}

Y_Soak_Impl(IonoCell)


