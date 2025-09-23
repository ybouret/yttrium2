//! \file

#ifndef IonoCell_Included
#define IonoCell_Included 1

#include "y/chemical/weasel.hpp"
#include "y/rtld/soak.hpp"

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
class IonoCell : public Soak<IonoCell>
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
    bool decl(const char * const argv);



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
    friend class Soak<IonoCell>;

    explicit IonoCell();           //!< setup
    virtual ~IonoCell() noexcept;  //!< cleanup
};

#endif // !IonoCell_Included
