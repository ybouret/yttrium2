
//! \file


#ifndef Y_Chemical_Conservation_Broken_Included
#define Y_Chemical_Conservation_Broken_Included 1


#include "y/chemical/plexus/conservation/law.hpp"
#include "y/protean/solo/heavy/list.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {
            //__________________________________________________________________
            //
            //
            //
            //! Broken Law decription
            //
            //
            //__________________________________________________________________
            class Broken
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                Broken(const Law &, const xreal_t) noexcept; //!< setup
                ~Broken() noexcept;                          //!< cleanup
                Broken(const Broken &) noexcept;             //!< duplicate
                Y_OSTREAM_PROTO(Broken);                     //!< display

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                static SignType Compare(const Broken &, const Broken &) noexcept; //!< \return increasing dc

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Law &law; //!< broken law
                xreal_t    xs;  //!< law excess
                xreal_t    dc;  //!< xs/law.norm = |delta C|

            private:
                Y_Disable_Assign(Broken); //!< discarding
            };

            typedef List<Broken>    BList; //!< alias
            typedef BList::NodeType BNode; //!< alias


        }

    }

}

#endif

