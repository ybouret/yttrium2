//! \file

#ifndef Y_HTable_Included
#define Y_HTable_Included 1


#include "y/core/linked/list/cxx.hpp"
#include "y/core/linked/pool/cxx.hpp"
#include "y/object.hpp"
#include "y/ability/recyclable.hpp"

namespace Yttrium
{

    class HTable : public Recyclable
    {
    public:
        static const char * const CallSign;
        static const size_t       MaxLoadFactor = 4;
        
        class Node : public Object
        {
        public:
            typedef CxxPoolOf<Node> Pool;
            typedef CxxListOf<Node> List;

            explicit Node() noexcept;
            virtual ~Node() noexcept;

            void     clear() noexcept;
            

            const size_t hkey;
            void * const data;
            Node *       next;
            Node *       prev;

        private:
            Y_Disable_Copy_And_Assign(Node);
        };
        typedef Node::List Slot;
        typedef bool (*Same)(const void * const, const void * const);


        explicit HTable(const size_t minSlots=4);
        virtual ~HTable() noexcept;

        virtual void free() noexcept;

        const Node * search(const size_t       hkey,
                            const void * const data,
                            Same const         same,
                            const Slot *   &   slot) const;

        Node *       search(const size_t       hkey,
                            const void * const data,
                            Same const         same,
                            Slot *   &         slot);


        Node * insert(const size_t hkey,
                      void * const data,
                      Same const   same);

        void remove(Node * const node) noexcept;

        bool remove(const size_t hkey,
                    void * const data,
                    Same const   same);



        const size_t    size; //!< keep inserted count
    private:
        class Code;
        Y_Disable_Copy_And_Assign(HTable);
        Code *          code;
        CxxPoolOf<Node> pool;
    };

}

#endif

