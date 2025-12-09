
#include "y/concurrent/thread/site.hpp"
#include "y/system/hardware.hpp"
#include "y/string/env.hpp"
#include "y/exception.hpp"
#include "y/string/tokenizer.hpp"
#include "y/container/algorithm/crop.hpp"
#include "y/container/algorithm/for-each.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/ascii/convert.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Concurrent
    {

        Site:: ~Site() noexcept
        {
            
        }

        const Site::Default_ Site::Default = {};

        void Site:: setup(const size_t nprocs,
                          const size_t offset,
                          const size_t stride)
        {
            assert(0==plist->size);
            if(nprocs<=0) throw Specific::Exception(CallSign,"no processors");
            if(stride<=0) throw Specific::Exception(CallSign,"zero stride");
            size_t cpu = offset;
            for(size_t i=nprocs;i>0;--i,cpu += stride)
            {
                plist << cpu;
            }
        }

        const char * const Site:: CallSign = "Concurrent::Site";

        Site:: Site(const size_t nprocs, const size_t offset, const size_t stride) :
        plist()
        {
            setup(nprocs,offset,stride);
        }



        const char * const Site:: Y_NUM_THREADS = "Y_NUM_THREADS";

        Site:: Site(const Default_ &) :
        Ingress<const PList>(),
        plist()
        {
            String info;
            if( Environment::Get(info,Y_NUM_THREADS) )
            {
                parse(info);
            }
            else
                setup( Hardware::NumProcs(), 0, 1 );
        }



        Site:: Site(const String &info) :
        Ingress<const PList>(),
        plist()
        {
            parse(info);
        }


        Site:: Site(const Site &site) :
        Ingress<const PList>(),
        plist(site.plist)
        {
        }

        Site & Site:: operator=(const Site &site)
        {
            Site _(site);
            plist->swapListFor(*(_.plist)); // low level swap
            return *this;
        }

        Y_Ingress_Impl(Site,plist)

        void Site:: parse(const String &info)
        {
            //std::cerr << "parsing '" << info << "'" << std::endl;

            const char * const str = info.c_str();
            if( strchr(str,COLON) )
            {
                return parseLinear(info);
            }

            if( strchr(str,COMMA) )
            {
                return parseCalled(info);
            }

            // default
            return parseLinear(info);
        }


        namespace
        {
            static inline size_t getField(const char * const name,
                                          String  &          word)
            {
                Algo::Crop(word,isblank);
                return ASCII::Convert::To<size_t>(word,name);
            }
        }

        void Site:: parseLinear(const String &info)
        {
            /*
            std::cerr << "parseLinear('" << info << "')" << std::endl;
            for (size_t i = 1; i <= info.size(); ++i)
                std::cerr << "[+] " << info[i] << std::endl;
             */
            
            Vector<String> words(WithAtLeast,3);
            Tokenizer::AppendTo(words,info,COLON);

            size_t nprocs = 0;
            size_t offset = 0;
            size_t stride = 1;
            switch(words.size())
            {
                case 3: stride = getField("stride",words[3]); // FALLTHRU
                case 2: offset = getField("offset",words[2]); // FALLTHRU
                case 1: nprocs = getField("nprocs",words[1]); break;
                default:
                    throw Specific::Exception(CallSign,"invalid number of linear fields");
            }
            setup(nprocs,offset,stride);
        }

        void Site:: parseCalled(const String &info)
        {
            Vector<String> words;
            Tokenizer::AppendTo(words,info,COMMA);

            for(size_t i=1;i<=words.size();++i)
            {
                plist << getField("processor",words[i]);
            }

            if(plist->size<=0)
                throw Specific::Exception(CallSign,"no processor found");
        }
    }
}
