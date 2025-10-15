
//! \file

#ifndef Y_Fit_Entity_Included
#define Y_Fit_Entity_Included 1

#include "y/container/writable.hpp"
#include "y/string.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            //__________________________________________________________________
            //
            //
            //
            //! named entity
            //
            //
            //__________________________________________________________________
            class Entity : public CountedObject
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param uid compatible name
                template <typename UID> inline
                explicit Entity(const UID & uid ) : name(uid) {}

                virtual ~Entity() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                const String & key() const noexcept; //!< \return name

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const String name; //!< identifier

            private:
                Y_Disable_Copy_And_Assign(Entity); //!< discarding
            };
        }

    }

}

#endif // !Y_Fit_Entity_Included
