
//! \file


#ifndef Y_Chemical_Entity_Included
#define Y_Chemical_Entity_Included 1


#include "y/string.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! Named entity
        //
        //
        //______________________________________________________________________
        class Entity : public CountedObject
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param id compatible id
            template <typename ID> inline
            explicit Entity(const ID &id) : name(id) {}
            explicit Entity();          //!< setup with emptu na,e
            virtual ~Entity() noexcept; //!< cleanup
            Y_OSTREAM_PROTO(Entity);    //!< display

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //_________________________________________________________________
            const String & key() const noexcept; //!< \return name

            //__________________________________________________________________
            //
            //
            // Members
            //
            //_________________________________________________________________
            const String name; //!< identifier

        private:
            Y_Disable_Copy_And_Assign(Entity); //!< discarding
        };

    }

}

#endif

