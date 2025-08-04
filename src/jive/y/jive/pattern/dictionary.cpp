#include "y/jive/pattern/dictionary.hpp"
#include "y/container/associative/suffix/map.hpp"
#include "y/type/destroy.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {

        static const char * const CallSign = "Jive::Dictionary";

        class Dictionary :: Code :
        public Object,
        public SuffixMap<String,Motif>
        {
        public:
            explicit Code()
            {
            }

            virtual ~Code() noexcept
            {
            }

            void record(const String &name,
                        const Motif  &motif)
            {
                if( !insert(name,motif) )
                    throw Specific::Exception(CallSign,"mutliple '%s'", name.c_str());
            }


        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        Dictionary:: ~Dictionary() noexcept
        {
            assert(code);
            Destroy(code);
        }

        Dictionary:: Dictionary() :
        code( new Code() )
        {
        }


        void Dictionary:: operator()(const String &n, Pattern * const p)
        {
            assert(0!=p);
            const Motif m(p);
            code->record(n,m);
        }

        void Dictionary:: operator()(const char * const name, Pattern * const p)
        {
            assert(0!=p);
            const Motif m(p);
            const String n(name);
            code->record(n,m);
        }

        Pattern * Dictionary:: query(const String &name)     const
        {
            assert(code);
            const Motif * const pp = code->search(name);
            if(!pp) return 0;
            return (**pp).clone();
        }

        Pattern * Dictionary:: query(const char * const name) const
        {
            const String _(name); return query(_);
        }


    }

}

