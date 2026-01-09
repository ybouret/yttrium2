

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
            class Character
            {
            public:
                typedef uint16_t DataType; //!< alias for bytes + control
                typedef uint32_t FreqType; //!< alias
                typedef uint64_t CodeType; //!< alias

                Y_OSTREAM_PROTO(Character);

                const DataType data;
                CodeType       code;
                unsigned       bits;
                FreqType       freq;
                Character *    next;
                Character *    prev;

                void     reset(const unsigned n, const FreqType f) noexcept;
                FreqType reduce() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Character);
                Character();
                ~Character() noexcept;
            };



          

        }

    }

}

#endif // !Y_Information_Pack_Character_Included

