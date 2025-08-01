
//! \file


#ifndef Y_Associative_DataBook_Included
#define Y_Associative_DataBook_Included 1

#include "y/protean/coop/heavy/list.hpp"

namespace Yttrium
{

    typedef  Protean::CoopHeavyList<uint64_t> DataList;
    typedef  DataList::PoolType               DataPool;
    typedef  DataList::NodeType               DataNode;
    
    class DataBook : public Ingress<const DataList>, public Recyclable
    {
    public:
        static const char * const CallSign;

        explicit DataBook(const DataPool &pool) noexcept;
        virtual ~DataBook() noexcept;

        virtual void free() noexcept;
        
        bool insert_(const uint64_t word);
        bool remove_(const uint64_t word) noexcept;
        bool search_(const uint64_t word) const noexcept;

        template <typename T> inline
        bool insert(const T &value)
        {
            return insert_( ToWord(value) );
        }

        template <typename T> inline
        bool remove(const T &value) noexcept
        {
            return remove_( ToWord(value) );
        }

        template <typename T> inline
        bool search(const T &value) const noexcept
        {
            return search_( ToWord(value) );
        }

        template <typename T> inline
        DataBook & operator+=(const T &value)
        {
            const uint64_t word = ToWord(value);
            if(!insert_(word)) ThrowMultiple(word);
            return *this;
        }

        template <typename T> inline
        DataBook & operator|=(const T &value)
        {
            (void) insert(value);
            return *this;
        }

        DataBook & operator|=(const DataBook &db)
        {
            for(const DataNode *node=db.list->head;node;node=node->next)
                (void) insert_( **node );
            return *this;
        }

        template <typename T> inline
        DataBook & operator-=(const T &value)
        {
            const uint64_t word = ToWord(value);
            if(!remove_(word)) ThrowNotFound(word);
            return *this;
        }

        DataBook & operator -= (const DataBook &db)
        {
            for(const DataNode *node=db.list->head;node;node=node->next)
                (void) remove_(**node);
            return *this;
        }


        bool includes(const DataBook &other) const noexcept;

        DataBook(const DataBook &);

        friend DataBook  operator | (const DataBook &, const DataBook &);
        friend DataBook  operator - (const DataBook &, const DataBook &);


    private:
        Y_Disable_Assign(DataBook);
        Y_Ingress_Decl();
        template <typename T> static inline
        uint64_t ToWord(const T &value) noexcept
        {
            union {
                uint64_t word;
                T        user;
            } alias = { 0 };
            alias.user = value;
            return alias.word;
        }

        static void ThrowMultiple(const uint64_t);
        static void ThrowNotFound(const uint64_t);

        DataList list;
    };
}

#endif

