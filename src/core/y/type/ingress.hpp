

#ifndef Y_Type_Ingress_Included
#define Y_Type_Ingress_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{

    template <typename T>
    class Ingress
    {
    public:
        Y_ARGS_EXPOSE(T,Interface);
    protected:
        inline explicit Ingress() noexcept {}
    public:
        inline virtual ~Ingress() noexcept {}


    private:
        Y_Disable_Copy_And_Assign(Ingress);
        virtual ConstInterface & locus() const noexcept = 0;
    };

#define Y_Ingress_Decl() virtual ConstInterface & locus() const noexcept
    
#define Y_Ingress_Impl(CLASS,LOCUS) \
CLASS::ConstInterface CLASS :: locus() const noexcept { return LOCUS; }

}

#endif

