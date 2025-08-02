
//! \file


#ifndef Y_Associative_DataBook_Included
#define Y_Associative_DataBook_Included 1

#include "y/protean/coop/heavy/list.hpp"

namespace Yttrium
{

    typedef Protean::HeavyNode<uint64_t> DataNode; //!< alias

    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //
        //! common DataBook ops
        //
        //
        //______________________________________________________________________
        class DataBook
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "DataBook"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit DataBook() noexcept; //!< setup
            virtual ~DataBook() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \param value integral value \return word
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

            //! locate function
            /**
             \param node output node
             \param list input list
             \param word searched value
             \return true => node, false: if node, insert after node, else push head
             */
            static bool Locate(DataNode * &       node,
                               ListOf<DataNode> & list,
                               const uint64_t     word) noexcept;

            static void     ThrowMultiple(const uint64_t); //!< throw multiple index
            static void     ThrowNotFound(const uint64_t); //!< throw index not found

            //! \return comparison of content
            static SignType CompareNodes(const DataNode * const, const DataNode * const) noexcept;

        private:
            Y_Disable_Copy_And_Assign(DataBook); //!< discarding
        };
    }


    //__________________________________________________________________________
    //
    //
    //
    //! DataBook
    //
    //
    //__________________________________________________________________________
    template <typename Threading = SingleThreadedClass>
    class DataBook :
    public Ingress< const Protean::CoopHeavyList<uint64_t,Threading> >,
    public Recyclable,
    public Core::DataBook
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef Protean::CoopHeavyList<uint64_t,Threading> ListType; //!< alias
        typedef typename ListType::PoolType                PoolType; //!< alias
        typedef Ingress<const ListType>                    BaseType; //!< alias
        typedef typename ListType::Lock                    Lock;     //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param pool shared pool
        inline DataBook(const PoolType &pool) : list(pool) {}

        //! duplicate \param db another book
        inline DataBook(const DataBook &db) :
        BaseType(), Recyclable(), Core::DataBook(),
        list(db.list) {}

        //! cleanup
        inline virtual ~DataBook() noexcept {}

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual void free() noexcept { list.free(); }


        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! search \param value target \return true if located matching word
        template <typename T>
        inline bool search(const T &value) const noexcept
        {
            volatile Lock lock(list);
            DataNode *    mine = 0;
            return Locate(mine,Coerce(*list),ToWord<T>(value));
        }

        //! remove \param value target \return true if removed matching word
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


        //! insert \param value target \return true if matching word was inserted
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

        //! permissive insert \param value target \return *this
        template <typename T>
        inline DataBook & operator|=(const T &value)
        {
            (void) insert(value);
            return *this;
        }

        //! loose insert \param value target \return *this
        template <typename T>
        inline DataBook & operator+=(const T &value)
        {
            if( !insert(value) ) ThrowMultiple(ToWord<T>(value));
            return *this;
        }

        //! \param db another book \return true if all db words are inside
        inline bool includes(const DataBook &db) const noexcept
        {
            if(db.list->size>list->size) return false;
            for(const DataNode *node=db.list->head;node;node=node->next)
            {
                if(!search(**node)) return false;
            }
            return true;
        }

        //! strict removal \param value target \return *this
        template <typename T>
        inline DataBook & operator -=(const T &value)
        {
            if(!remove(value)) ThrowNotFound( ToWord<T>(value) );
            return *this;
        }

        //! strict removal \param db another book \return *this
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

        //! \param lhs book \param rhs book \return strict difference
        inline friend DataBook operator-(const DataBook &lhs, const DataBook &rhs)
        {
            DataBook db(lhs);
            return db -= rhs;
        }
        
    private:
        inline virtual typename BaseType::ConstInterface & locus() const noexcept { return list; }
        Y_Disable_Assign(DataBook); //!< discarding
        ListType list;              //!< operating list

    };



}

#endif

