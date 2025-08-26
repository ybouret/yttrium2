//! \file


#ifndef Y_Chemical_Indexed_Included
#define Y_Chemical_Indexed_Included 1


#include "y/chemical/type/entity.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        enum Level
        {
            TopLevel,
            SubLevel,
            AuxLevel
        };

        class Indexed : public Entity
        {
        public:
            static const unsigned MaxLevel = AuxLevel+1;


            explicit Indexed(const size_t top);

            template <typename ID> inline
            explicit Indexed(const ID &id, const size_t top) :
            Entity(id),
            indx()
            {
                setup(top);
            }
            
            virtual ~Indexed() noexcept;

            const size_t indx[MaxLevel];

        private:
            Y_Disable_Copy_And_Assign(Indexed);
            void setup(const size_t) noexcept;
        };

    }

}

#endif

