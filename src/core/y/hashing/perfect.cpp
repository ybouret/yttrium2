
#include "y/hashing/perfect.hpp"
#include "y/container/tree/suffix.hpp"
#include "y/check/usual.hpp"
#include "y/type/destroy.hpp"
#include "y/check/static.hpp"
#include "y/system/exception.hpp"
#include "y/string.hpp"
#include "y/string/length.hpp"


namespace Yttrium
{
    namespace Hashing
    {

        class Perfect:: Code : public Object, public SuffixTree
        {
        public:

            inline explicit Code() : Object(), SuffixTree()
            {
            }

            inline virtual ~Code() noexcept
            {
                free();
            }

        private:
            Y_Disable_Copy_And_Assign(Code);
        };


        const char * const Perfect:: CallSign = "Hashing::Perfect";

        Perfect:: Perfect() : code( new Code() )
        {
        }

        Perfect:: ~Perfect() noexcept
        {
            assert(code);
            Destroy(code);
        }


        void Perfect:: operator()(const void *path, const size_t size, const int key)
        {
            Y_STATIC_CHECK(sizeof(void*)>=sizeof(int),BadSystem);
            assert(0!=code);
            assert( Good(path,size) );
            assert(key>0);

            const uint8_t * const iter = static_cast<const uint8_t *>(path);

            union {
                void * p;
                int    k;
            } alias = { 0 };
            alias.k = key; assert(0!=alias.p);

            if( ! code->insert(iter,size,alias.p) )
            {
                throw Specific::Exception(CallSign,"invalid key %d or multiple path",key);
            }
        }


        void Perfect:: operator()(const char * const text, const int key)
        {
            (*this)(text, StringLength(text), key);
        }

        void Perfect:: operator()(const Memory::ReadOnlyBuffer &buf, const int key)
        {
            (*this)(buf.ro(), buf.length(), key);
        }

    }

}
