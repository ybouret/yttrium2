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


bool IonoCell:: declare(const char * const argv)
{
    assert(0!=argv);
    Y_Soak_Bool(
                const String data = argv;
                weasel( Jive::Module::OpenData(data,data), lib, eqs);
                std::cerr << "lib=" << lib << std::endl;
                );
}

Y_Soak_Meth(bool,IonoCell,declare,(const char *const argv), (argv) )
