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


bool IonoCell:: parse(const char * const argv)
{
    assert(0!=argv);
    Y_Spyndle_Boolean(
                      const String data = argv;
                      weasel( Jive::Module::OpenData(data,data), lib, eqs);
                      std::cerr << "lib=" << lib << std::endl;
                      );
}


Y_Spyndle_Meth(bool,IonoCell,parse,(const char *const argv), (argv) )


size_t IonoCell:: numSpecies() const noexcept
{
    return lib->size();
}

Y_Spyndle_Meth(size_t,IonoCell,numSpecies,(),())


const char * IonoCell:: getSpeciesName(const size_t i) const noexcept
{
    const Species &sp = *lib->fetch(i+1);
    return sp.name.c_str();
}

Y_Spyndle_Meth(const char *,IonoCell,getSpeciesName,(const size_t i),(i))


int IonoCell:: getSpeciesZ(const size_t i) const noexcept
{
    const Species &sp = *lib->fetch(i+1);
    return sp.z;
}

Y_Spyndle_Meth(int,IonoCell,getSpeciesZ,(const size_t i),(i))


const char * IonoCell:: getSpeciesLaTeX(const size_t i) const noexcept
{
    const Species &sp = *lib->fetch(i+1);
    return sp.tex.c_str();
}

Y_Spyndle_Meth(const char *,IonoCell,getSpeciesLaTeX,(const size_t i),(i))

double IonoCell:: getD(const char * const name) const
{
    const String _(name);
    const double res = weasel.diffusionCoefficient(name);
    return res;
}

Y_Spyndle_Meth(double,IonoCell,getD,(const char * const name),(name))
