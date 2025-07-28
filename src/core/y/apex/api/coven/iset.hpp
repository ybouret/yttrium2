
//! \file

#ifndef Y_Coven_ISet_Included
#define Y_Coven_ISet_Included 1

#include "y/apex/api/coven/ilist.hpp"


namespace Yttrium
{

    namespace Coven
    {

        //______________________________________________________________________
        //
        //
        //
        //! Set of indices
        //
        //
        //______________________________________________________________________
        class ISet : public Ingress<const IList>
        {
        public:
            explicit ISet(const IPool &pool) noexcept;
            virtual ~ISet() noexcept;
            ISet(const ISet &);

            ISet & operator<<(INode * const node);

            bool has(const size_t) const noexcept;
            void remove(const size_t) noexcept;

            friend bool operator==(const ISet &, const ISet &) noexcept;



        private:
            IList list; //!< inner ordered list
            Y_Disable_Assign(ISet); //!< discarding
            virtual ConstInterface & locus() const noexcept;
        };

    }

}

#endif

