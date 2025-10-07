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
    bool         parse(const char * const argv);                 //!< send code to weasel \param argv code \return true iff success
    size_t       numSpecies() const noexcept;                    //!< species in library \return M
    const char * getSpeciesName(const size_t i)  const noexcept; //!< \param i in [0:M-1] \return species name
    int          getSpeciesZ(const size_t i)     const noexcept; //!< \param i in [0:M-1] \return species charge
    const char * getSpeciesLaTeX(const size_t i) const noexcept; //!< \param i in [0:M-1] \return LaTeX formula
    double       getD(const char * const name)   const;          //!< \param name species name \return D from table

    //__________________________________________________________________________
    //
    //
    // Members
    //
    //__________________________________________________________________________
    Weasel &   weasel; //!< handling code
    Library    lib;    //!< current library
    Equilibria eqs;    //!< current equilibria

private:
    Y_Disable_Copy_And_Assign(IonoCell); //!< discarding
    friend class Spyndle<IonoCell>;

    explicit IonoCell();           //!< setup
    virtual ~IonoCell() noexcept;  //!< cleanup
};

#endif // !IonoCell_Included
