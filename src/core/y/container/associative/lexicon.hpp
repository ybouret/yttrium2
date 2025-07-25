//! \file


#ifndef Y_Lexicon_Included
#define Y_Lexicon_Included 1

#include "y/container/associative.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Interface for Maps
    //
    //
    //__________________________________________________________________________
    template <typename KEY, typename T>
    class Lexicon : public Associative<KEY,T>
    {
    public:
        Y_Args_Declare(T,Type);                       //!< aliases
        Y_Args_Declare(KEY,Key);                      //!< aliases
        virtual bool insert(ParamKey, ParamType) = 0; //!< \return true if (key,value) was inserted
        inline virtual ~Lexicon() noexcept {}         //!< cleanup
    protected:
        inline explicit Lexicon() noexcept : Associative<KEY,T>() {} //!< setup

    private:
        Y_Disable_Copy_And_Assign(Lexicon); //!< discarding
    };

}

#endif

