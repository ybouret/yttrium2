//

#ifndef Y_Type_Ingress_Included
#define Y_Type_Ingress_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! reveal a part of a class
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class Ingress
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_ARGS_EXPOSE(T,Interface); //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        inline explicit Ingress() noexcept {} //!< initialize
    public:
        inline virtual ~Ingress() noexcept {} //!< cleanup

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        inline ConstInterface & operator*()  const noexcept { return locus(); }               //!< access \return const interface
        inline Interface &      operator*()        noexcept { return (Interface&)locus(); }   //!< access \return interface
        inline ConstInterface * operator->() const noexcept { return & locus(); }             //!< access \return const interface address
        inline Interface      * operator->()       noexcept { return & (Interface&)locus(); } //!< access \return interface address

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
    private:
        Y_Disable_Copy_And_Assign(Ingress);                  //!< discarding
        virtual ConstInterface & locus() const noexcept = 0; //!< interface \return its location
    };

    //! helper to declare Ingress
#define Y_Ingress_Decl() virtual ConstInterface & locus() const noexcept

    //! helper to implement Ingress
#define Y_Ingress_Impl(CLASS,LOCUS) \
CLASS::ConstInterface  & CLASS :: locus() const noexcept { return LOCUS; }

}

#endif

