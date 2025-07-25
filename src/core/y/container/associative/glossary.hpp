
//! \file


#ifndef Y_Glossary_Included
#define Y_Glossary_Included 1

#include "y/container/associative.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Interface for Sets
    //
    //
    //__________________________________________________________________________
    template <typename KEY, typename T>
    class Glossary : public Associative<KEY,T>
    {
    public:
        Y_Args_Declare(T,Type);                 //!< alias
        virtual bool     insert(ParamType) = 0; //!< \return true if object was inserted
        inline  virtual ~Glossary() noexcept {} //!< cleanup
    protected:
        inline explicit Glossary() noexcept : Associative<KEY,T>() {} //!< setup

    private:
        Y_Disable_Copy_And_Assign(Glossary); //!< discarding
    };

}

#endif

