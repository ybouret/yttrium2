
#include "y/memory/object/factory/api.hpp"
#include "y/memory/stealth.hpp"
#include "y/calculus/alignment.hpp"
#include "y/memory/object/blocks.hpp"
#include "y/system/exception.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {


            const char * const FactoryAPI:: CallSign = "Memory::Object::Factory";



            class FactoryAPI:: Code
            {
            public:
                static bool Allocated;

                inline ~Code() noexcept
                {
                    if(!Allocated)
                        Libc::Error::Critical(EINVAL, "%s was not allocated", FactoryAPI::CallSign);
                    Allocated = false;
                }

                inline Code(const size_t userPageBytes)   :
                blocks( AllowedWith(userPageBytes) )
                {
                }

                Blocks blocks;



            private:
                Y_Disable_Copy_And_Assign(Code);
                static inline size_t AllowedWith(const size_t userPageBytes)
                {
                    if(Allocated) throw Specific::Exception(FactoryAPI::CallSign,"already allocated!!");
                    Allocated = true;
                    return userPageBytes;
                }
            };

            bool FactoryAPI:: Code:: Allocated = false;


            namespace
            {
                static void * codeWorkspace[ Alignment::WordsFor<FactoryAPI::Code>::Count ];
            }




            FactoryAPI:: FactoryAPI(const size_t userPageBytes) :
            code( new ( Y_Memory_BZero(codeWorkspace) ) Code(userPageBytes) )
            {

            }

            FactoryAPI:: ~FactoryAPI() noexcept
            {
                assert(0!=code);
                Stealth::Zero( Destructed(code), sizeof(codeWorkspace) );
                Coerce(code) = 0;
            }


        }
    }
}


