
#include "y/container/ordered/data-book.hpp"
#include "y/system/exception.hpp"
#include "y/format/hexadecimal.hpp"

namespace Yttrium
{
    DataBook:: DataBook(const DataPool &pool) noexcept :
    list(pool)
    {
    }

    DataBook:: ~DataBook() noexcept
    {

    }

    Y_Ingress_Impl(DataBook,list)

    void DataBook:: free() noexcept
    {
        list.free();
    }

    bool DataBook:: insert_(const uint64_t word)
    {
        switch(list->size)
        {
            case 0: list << word; return true;
            case 1:
                switch( Sign::Of(word,**(list->head)) )
                {
                    case Negative: list >> word; break;
                    case Positive: list << word; break;
                    case __Zero__: return false;
                }
                return true;
            default:
                break;
        }
        assert(list->size>1);
        DataNode * lower = list->head;
        switch(Sign::Of(word,**lower))
        {
            case Negative: list >> word; return true;
            case __Zero__: return false;
            case Positive:
                break;
        }

        {
            DataNode * const upper = list->tail; assert(upper!=lower);
            switch( Sign::Of(word,**upper) )
            {
                case Positive: list << word; return true;
                case __Zero__: return false;
                case Negative:
                    break;
            }

            while(lower->next!=upper)
            {
                DataNode * const probe = lower->next;
                switch( Sign::Of(word,**probe) )
                {
                    case Negative: goto INSERT;
                    case __Zero__: return false;
                    case Positive: break;
                }
                lower = probe;
            }
        INSERT:
            assert(word>**lower);
            assert(word<**(lower->next));
            list->insertAfter(lower,list.pool.summon(word));
            return true;
        }

    }

    bool DataBook:: remove_(const uint64_t word) noexcept
    {
        for(DataNode *node=list->head;node;node=node->next)
        {
            if( **node == word )
            {
                list.cut(node);
            }
        }
        return false;
    }

    bool DataBook:: search_(const uint64_t word) const noexcept
    {
        for(DataNode *node=list->head;node;node=node->next)
        {
            if( **node == word )
            {
                return true;
            }
        }
        return false;
    }

    const char * const DataBook::CallSign = "DataBook";

    void DataBook:: ThrowMultiple(const uint64_t word)
    {
        throw Specific::Exception(CallSign,"insert multiple '%s'", Hexadecimal(word,Concise).c_str());
    }

    void DataBook:: ThrowNotFound(const uint64_t word)
    {
        throw Specific::Exception(CallSign,"remove unknown '%s'", Hexadecimal(word,Concise).c_str());
    }

}
