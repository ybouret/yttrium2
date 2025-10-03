//! \file

#ifndef IonoCell_Included
#define IonoCell_Included 1

#include "y/chemical/weasel.hpp"
#include "y/rtld/spyndle.hpp"

using namespace Yttrium;
using namespace Chemical;

//______________________________________________________________________________
//
//
//
//! chemistry for python
//
//
//______________________________________________________________________________
class IonoCell : public Spyndle<IonoCell>
{
public:
    //__________________________________________________________________________
    //
    //
    // Definitions
    //
    //__________________________________________________________________________
    static const char * const CallSign; //!< "IonoCell"

    //__________________________________________________________________________
    //
    //
    // Methods
    //
    //__________________________________________________________________________
    bool         parse(const char * const argv); //!< send code to weasel
    size_t       numSpecies() const noexcept;      //!< species in library
    const char * getSpeciesName(const size_t i)  const noexcept;
    int          getSpeciesZ(const size_t i)     const noexcept;
    const char * getSpeciesLaTeX(const size_t i) const noexcept;

    //__________________________________________________________________________
    //
    //
    // Members
    //
    //__________________________________________________________________________
    Weasel &   weasel;
    Library    lib;
    Equilibria eqs;

private:
    Y_Disable_Copy_And_Assign(IonoCell); //!< discarding
    friend class Spyndle<IonoCell>;

    explicit IonoCell();           //!< setup
    virtual ~IonoCell() noexcept;  //!< cleanup
};

#endif // !IonoCell_Included
