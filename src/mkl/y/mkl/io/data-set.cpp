#include "y/mkl/io/data-set.hpp"
#include "y/string/format.hpp"
#include "y/format/decimal.hpp"
#include <cstring>
#include "y/exception.hpp"
#include "y/string/tokenizer.hpp"
#include "y/container/sequence/vector.hpp"

namespace Yttrium
{
    namespace MKL
    {

        DataColumn:: ~DataColumn() noexcept
        {
        }

        const size_t & DataColumn:: key() const noexcept { return indx; }
        
        void DataColumn:: append(const String &data)
        {
            grow(addr,data,name);
        }

        void DataColumn:: format()
        {
            void * const buf = memset((char*)name,0,sizeof(name));
            String       uid = "col#"; uid += Decimal(indx).c_str();
            memcpy(buf,uid.c_str(),uid.size());
        }
    }

    namespace MKL
    {

        const char * const DataSet:: CallSign = "MKL::DataSet";
        
        DataSet:: ~DataSet() noexcept
        {
        }

        DataSet:: DataSet() : DataColumns()
        {
        }


        DataSet & DataSet:: add(DataColumn * const dc)
        {
            assert(0!=dc);
            const DataColumn::Pointer p = dc;
            if(!insert(p))
                throw Specific::Exception(CallSign,"multiple %s", p->name);
            return *this;
        }

        void DataSet:: load(InputStream &fp)
        {
            static const char   sep[] = " \t";
            static const size_t num   = strlen(sep);

            Vector<String> words;
            String         line;
            size_t         iline=0;
            while(fp.gets(line))
            {
                ++iline;
                if(line.size()<=0) continue;
                if('#' == line[1]) continue;
                words.free();
                Tokenizer::AppendTo(words,line,sep,num);

                for(Iterator it=begin();it!=end();++it)
                {
                    DataColumn & dc = **it;
                    const size_t id = dc.indx;
                    if(id<=0||id>words.size())
                        throw Specific::Exception(CallSign,"missing %s at line %s", dc.name, Decimal(iline).c_str());
                    dc.append(words[id]);
                }

            }
        }


    }

}
