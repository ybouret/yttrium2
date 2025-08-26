
//! \file


#ifndef Y_Chemical_Entity_Included
#define Y_Chemical_Entity_Included 1


#include "y/string.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        class Entity : public CountedObject
        {
        public:
            template <typename ID> inline
            explicit Entity(const ID &id) : name(id)
            {
            }

            explicit Entity();
            virtual ~Entity() noexcept;
            Y_OSTREAM_PROTO(Entity);


            const String & key() const noexcept;

            const String name;

        private:
            Y_Disable_Copy_And_Assign(Entity);
        };

    }

}

#endif

