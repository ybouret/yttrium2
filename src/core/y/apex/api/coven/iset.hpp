
//! \file

#ifndef Y_Coven_ISet_Included
#define Y_Coven_ISet_Included 1

#include "y/apex/api/coven/ilist.hpp"


namespace Yttrium
{

    namespace Coven
    {

        class ISet : public Ingress<const IList>
        {
        public:
            explicit ISet(const IPoolType &pool) noexcept;
            virtual ~ISet() noexcept;
            ISet(const ISet &);

            ISet & operator<<(INode * const node);

            bool has(const size_t) const noexcept;

            friend bool operator==(const ISet &, const ISet &) noexcept;



        private:
            Y_Disable_Assign(ISet);
            virtual ConstInterface & locus() const noexcept;
            IList list;

        };

    }

}

#endif

