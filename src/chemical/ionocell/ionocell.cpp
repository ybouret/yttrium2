#include "ionocell.hpp"

IonoCell:: ~IonoCell() noexcept
{
}

const char * const IonoCell:: CallSign = "IonoCell";

IonoCell:: IonoCell() : Spyndle<IonoCell>(),
weasel( Weasel::Instance() ),
lib(),
eqs()
{
}

Y_Spyndle(IonoCell)


bool IonoCell:: declare(const char * const argv)
{
    assert(0!=argv);
    Y_Spyndle_Boolean(
                      const String data = argv;
                      weasel( Jive::Module::OpenData(data,data), lib, eqs);
                      std::cerr << "lib=" << lib << std::endl;
                      );
}


Y_Spyndle_Meth(bool,IonoCell,declare,(const char *const argv), (argv) )

#if 0

size_t IonoCell:: numSpecies() const noexcept
{
    return lib->size();
}

Y_Soak_Meth(size_t,IonoCell,numSpecies,(),())

const char * IonoCell:: getSpeciesName(const size_t i) const noexcept
{
    const Species &sp = *lib->fetch(i+1);
    return sp.name.c_str();
}

Y_Soak_Meth(const char *,IonoCell,getSpeciesName,(const size_t i),(i))

int IonoCell:: getSpeciesCharge(const size_t i) const noexcept
{
    const Species &sp = *lib->fetch(i+1);
    return sp.z;
}

Y_Soak_Meth(int,IonoCell,getSpeciesCharge,(const size_t i),(i))
#endif

