
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
            assert(0!=code);
            const Joint::Segments &seg = *code;

            init(os,indent);
            ++indent;
            bool hasData = false;
            for(unsigned bs=Joint::Segments::MinShift;bs<=Joint::Segments::MaxShift;++bs)
            {
                const Joint::Segments::Slot &slot = seg[bs];
                if(slot.size>0)
                {
                    hasData = true;
                    XML::Indent(os,indent) << '<' << '2' << '^' << bs <<  '>' << std::endl;
                }

            }
            if(!hasData) XML::Indent(os,indent) << "Empty " << CallSign << std::endl;
            --indent;
            quit(os,indent);
        }

    }

}

