
#include "y/container/ordered/data-book.hpp"
#include "y/system/exception.hpp"
#include "y/format/hexadecimal.hpp"

namespace Yttrium
{

    namespace Core
    {

        DataBook::  DataBook() noexcept {}
        DataBook:: ~DataBook() noexcept {}

        const char * const DataBook::CallSign = "DataBook";

        void DataBook:: ThrowMultiple(const uint64_t word)
        {
            throw Specific::Exception(CallSign,"insert multiple '%s'", Hexadecimal(word,Concise).c_str());
        }

        void DataBook:: ThrowNotFound(const uint64_t word)
        {
            throw Specific::Exception(CallSign,"remove unknown '%s'", Hexadecimal(word,Concise).c_str());
        }


        bool DataBook:: Locate( DataNode * &node, ListOf<DataNode> &list, const uint64_t word) noexcept
        {
            assert( 0 == node );

            //std::cerr << "Looking for " << word << " in " << list << std::endl;
            switch(list.size)
            {
                case 0: assert(0==node); return false; // shall pushHead
                    
                case 1:
                    switch( Sign::Of(word,**list.head) )
                    {
                        case Negative: assert(0==node);  return false; // shall pushHead
                        case Positive: node = list.head; return false; // shall insertAfter head
                        case __Zero__: break;
                    }
                    node = list.head; return true; // success
                default:
                    break;
            }

            DataNode * const upper = list.tail;
            switch( Sign::Of(word,**upper) )
            {
                case __Zero__: node = upper; return true;
                case Positive: node = upper; return false; // shall insert after upper
                case Negative: break;
            }
            //std::cerr << "-> before tail@" << **upper << std::endl;


            DataNode *lower = list.head; assert(lower!=upper);
            switch( Sign::Of(word,**lower) )
            {
                case __Zero__: node = lower;    return true;
                case Negative: assert(0==node); return false; // shall pushHead
                case Positive: break;
            }
            //std::cerr << "-> after head@" << **lower << std::endl;


            while(lower->next!=upper)
            {
                assert(word<**upper);
                assert(word>**lower);
                DataNode * const probe = lower->next;
                switch(Sign::Of(word,**probe) )
                {
                    case Negative: node  = lower; return false; // shall insert after lower
                    case __Zero__: node  = probe; return true;  // success
                    case Positive: lower = probe; continue;
                }
            }
            node = lower;
            return false;

        }

#if 0
        const DataNode * DataBook:: Search(const ListOf<DataNode> &list, const uint64_t word) noexcept
        {
            switch(list.size)
            {
                case 0: return 0;
                case 1: return word == **list.head ? list.head : 0;
                default:
                    break;
            }

            DataNode * const upper = list.tail;
            switch( Sign::Of(word,**upper) )
            {
                case __Zero__: return upper;
                case Positive: return 0;
                case Negative: break;
            }

            DataNode *lower = list.head; assert(lower!=upper);
            switch( Sign::Of(word,**lower) )
            {
                case __Zero__: return lower;
                case Negative: return 0;
                case Positive: break;
            }

            for(lower=lower->next;lower!=upper;lower=lower->next)
            {
                switch(Sign::Of(word,**lower) )
                {
                    case Negative: return 0;
                    case __Zero__: return lower;
                    case Positive: continue;
                }
            }
            return 0;



        }
#endif


    }
#if 0
    DataBook:: DataBook(const DataPool &pool) noexcept :
    list(pool)
    {
    }

    DataBook:: ~DataBook() noexcept
    {

    }

    DataBook :: DataBook(const DataBook &db) :
    list(db.list)
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
                return true;
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


    bool DataBook:: includes(const DataBook &other) const noexcept
    {
        if(other.list->size>list->size) return false;

        for(const DataNode *node=other.list->head;node;node=node->next)
        {
            if(! search(**node) ) return false;
        }
        return true;
    }

    DataBook  operator | (const DataBook &lhs, const DataBook &rhs)
    {
        DataBook db(lhs);
        db |= rhs;
        return db;
    }

    DataBook  operator - (const DataBook &lhs, const DataBook &rhs)
    {
        //std::cerr << "{" << lhs << " - " << rhs << "}" << std::endl;
        DataBook db(lhs);
        db -= rhs;
        return db;
    }
#endif


}
