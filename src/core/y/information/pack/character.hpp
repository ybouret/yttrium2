

//! \file

#ifndef Y_Information_Pack_Character_Included
#define Y_Information_Pack_Character_Included 1

#include "y/core/setup.hpp"
#include "y/ostream-proto.hpp"

namespace Yttrium
{

    namespace Information
    {
        namespace Pack
        {
            //__________________________________________________________________
            //
            //
            //
            //! embedded character statistics
            //
            //
            //__________________________________________________________________
            class Character
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef uint16_t DataType; //!< alias for bytes + control
                typedef uint32_t FreqType; //!< alias
                typedef uint64_t CodeType; //!< alias


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const DataType data; //!< original data
                CodeType       code; //!< current code
                unsigned       bits; //!< current bits
                FreqType       freq; //!< current frequency
                Character *    next; //!< for list
                Character *    prev; //!< for list

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                Y_OSTREAM_PROTO(Character);              //!< display
                void     reset(const unsigned) noexcept; //!< reset with nbits
                FreqType reduce()              noexcept; //!< reduce frequency \return new frequency

            private:
                Y_Disable_Copy_And_Assign(Character); //!< discarding
                Character();           //!< discarding
                ~Character() noexcept; //!< discarding
            };



          

        }

    }

}

#endif // !Y_Information_Pack_Character_Included

