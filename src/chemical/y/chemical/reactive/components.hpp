//! \file

#ifndef Y_Chemical_Components_Included
#define Y_Chemical_Components_Included 1


#include "y/chemical/reactive/actors.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! Base class for Equilibrium
        //
        //
        //______________________________________________________________________
        class Components : public Indexed
        {
        public:
            static const char * const Arrows;   //!< "<=>"
            static const char * const Prod;     //!< "Prod"
            static const char * const Reac;     //!< "Reac"

            template <typename ID> inline
            explicit Components(const ID & id, const size_t top) :
            Indexed(id,top),
            reac(),
            prod()
            {
            }
            virtual ~Components() noexcept;
            Y_OSTREAM_PROTO(Components);

            void p(const unsigned, const Species &);
            void r(const unsigned, const Species &);
            void p(const Species &);
            void r(const Species &);

            const Actors reac;
            const Actors prod;
        private:
            Y_Disable_Copy_And_Assign(Components);
        };
    }

}

#endif

