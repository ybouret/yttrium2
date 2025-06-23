
#include "y/information/bwt/transformer.hpp"
#include "y/type/destroy.hpp"
#include "y/object.hpp"
#include "y/object/school-of.hpp"
#include "y/core/utils.hpp"
#include "y/check/usual.hpp"
#include "y/information/bwt/bwt.hpp"

namespace Yttrium
{
    namespace Information
    {

        class BWT_Transformer :: Code : public Object,
        public Memory::SchoolOf<size_t>
        {
        public:

            inline explicit Code(const size_t n) :
            Object(),
            Memory::SchoolOf<size_t>(MaxOf<size_t>(n,8))
            {
            }

            inline virtual ~Code() noexcept
            {
            }


        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        BWT_Transformer:: BWT_Transformer() noexcept :
        code(0)
        {
        }

        BWT_Transformer:: ~BWT_Transformer() noexcept
        {
            if(code) Destroy(code);
        }


        void BWT_Transformer:: make(const size_t length)
        {
            if(0==code)
            {
                code = new Code(length);
            }
            else
            {
                if(code->count<length)
                {
                    Destroy(code);
                    code = new Code(length);

                }
            }

            assert(0!=code);
            assert(code->count>=length);
        }

        size_t BWT_Transformer:: encode(void * const       target,
                                        const void * const source,
                                        const size_t       length)
        {
            assert( Good(target,length) );
            assert( Good(source,length) );
            make(length);
            return BWT::Encode(target, source, length, code->entry);
        }

        void   BWT_Transformer:: decode(void * const       target,
                                        const void * const source,
                                        const size_t       length,
                                        const size_t       primary)
        {
            assert( Good(target,length) );
            assert( Good(source,length) );
            make(length);
            BWT::Decode(target,source,length,code->entry,primary);
        }

    }

}

