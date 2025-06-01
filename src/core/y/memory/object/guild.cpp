
#include "y/memory/object/guild.hpp"
#include "y/memory/object/factory.hpp"
#include "y/memory/object/blocks.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {

            class Guild:: Code
            {
            public:

                Code()
                {

                }

                ~Code() noexcept
                {
                }


                Code * Create(const size_t blockSize)
                {
                    return 0;
                }

            private:
                Y_Disable_Copy_And_Assign(Code);
            };



            Guild:: Guild(const size_t blockSize) :
            code( 0 )
            {
            }


            Guild:: ~Guild() noexcept
            {
            }
            

        }
    }

}
