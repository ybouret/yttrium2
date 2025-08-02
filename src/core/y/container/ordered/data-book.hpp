
//! \file


#ifndef Y_Associative_DataBook_Included
#define Y_Associative_DataBook_Included 1

#include "y/protean/coop/heavy/list.hpp"

namespace Yttrium
{

    typedef Protean::HeavyNode<uint64_t> DataNode;

    namespace Core
    {
        class DataBook
        {
        public:
            static const char * const            CallSign;

            explicit DataBook() noexcept;
            virtual ~DataBook() noexcept;

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

            static bool Locate(DataNode * &node, ListOf<DataNode> &list, const uint64_t word) noexcept;

            static void ThrowMultiple(const uint64_t);
            static void ThrowNotFound(const uint64_t);

        private:
            Y_Disable_Copy_And_Assign(DataBook);
        };
    }

    template <typename Threading = SingleThreadedClass>
    class DataBook :
    public Ingress< const Protean::CoopHeavyList<uint64_t,Threading> >,
    public Recyclable,
    public Core::DataBook
    {
    public:
        typedef Protean::CoopHeavyList<uint64_t,Threading> ListType;
        typedef typename ListType::PoolType                PoolType;
        typedef Ingress<const ListType>                    BaseType;
        typedef typename ListType::Lock                    Lock;

        inline DataBook(const PoolType &pool) : list(pool) {}
        inline virtual ~DataBook() noexcept {}
        inline DataBook(const DataBook &db) : list(db.list) {}

        inline virtual void free() noexcept { list.free(); }

        template <typename T>
        inline bool search(const T &value) const noexcept
        {
            volatile Lock lock(list);
            DataNode *    mine = 0;
            return Locate(mine,Coerce(*list),ToWord<T>(value));
        }

        template <typename T>
        inline bool remove(const T &value) noexcept
        {
            volatile Lock lock(list);
            DataNode *    mine = 0;
            if(!Locate(mine,*list,ToWord<T>(value))) return false;
            assert(0!=mine);
            list.pool.banish( list->pop(mine) );
            return true;
        }

        static SignType CompareNodes(const DataNode * const lhs, const DataNode * const rhs) noexcept
        {
            return Sign::Of( **lhs, **rhs );
        }

        template <typename T>
        inline bool insert(const T &value)
        {
            volatile Lock lock(list);
            DataNode *     mine = 0;
            const uint64_t word = ToWord<T>(value);
            if(Locate(mine,*list,word)) return false;
            DataNode * const node = list.pool.summon(word);
            if(!mine) list->pushHead( node );
            else      list->insertAfter(mine,node);
            assert(list->isOrderedBy(CompareNodes,Sign::StriclyIncreasing));
            return true;
        }

        template <typename T>
        inline DataBook & operator|=(const T &value)
        {
            (void) insert(value);
            return *this;
        }

        template <typename T>
        inline DataBook & operator+=(const T &value)
        {
            if( !insert(value) ) ThrowMultiple(ToWord<T>(value));
            return *this;
        }

        inline bool includes(const DataBook &db) const noexcept
        {
            if(db.list->size>list->size) return false;
            for(const DataNode *node=db.list->head;node;node=node->next)
            {
                if(!search(**node)) return false;
            }
            return true;
        }

        template <typename T>
        inline DataBook & operator -=(const T &value)
        {
            if(!remove(value)) ThrowNotFound( ToWord<T>(value) );
            return *this;
        }

        inline DataBook & operator -=(const DataBook &db)
        {
            if(this == &db)
                free();
            else
            {
                for(const DataNode *node=db.list->head;node;node=node->next)
                    *this -= **node;
            }
            return *this;
        }

        inline friend DataBook operator-(const DataBook &lhs, const DataBook &rhs)
        {
            DataBook db(lhs);
            return db -= rhs;
        }






    private:
        Y_Disable_Assign(DataBook);
        inline virtual typename BaseType::ConstInterface & locus() const noexcept { return list; }
        ListType list;

    };

#if 0
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
#endif
    
}

#endif

