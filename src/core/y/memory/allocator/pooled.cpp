
#include "y/memory/allocator/pooled.hpp"
#include "y/memory/joint/segments.hpp"
#include "y/memory/stealth.hpp"

namespace Yttrium
{
    namespace Memory
    {


        const char * const Pooled:: CallSign = "Memory::Pooled";


        class Pooled :: Code : public  Joint::Segments
        {
        public:
            explicit Code() : Joint::Segments()
            {
            }


            virtual ~Code() noexcept
            {
            }

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        namespace
        {
            static void * codeWorkspace[ Alignment::WordsFor<Pooled::Code>::Count ];
        }

        Pooled:: Pooled() :
        code( new (Y_Memory_BZero(codeWorkspace)) Code() )
        {
        }

        Pooled:: ~Pooled() noexcept
        {
            assert(0!=code);
            Stealth::DestructedAndZeroed(code);
            Coerce(code) = 0;
        }

        void Pooled:: display(std::ostream &os, size_t indent) const
        {
            init(os,indent);

            quit(os,indent);
        }

    }

}

