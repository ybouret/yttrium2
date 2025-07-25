//! \file

#ifndef Y_HTable_Included
#define Y_HTable_Included 1


#include "y/core/linked/list/cxx.hpp"
#include "y/core/linked/pool/cxx.hpp"
#include "y/object.hpp"
#include "y/ability/recyclable.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Low-level Hash Table
    //
    //
    //__________________________________________________________________________
    class HTable : public Recyclable, public Releasable
    {
    public:

        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const CallSign;           //!< "HTable"
        static const size_t       MaxLoadFactor = 4;  //!< Maximum Load Factor


        //______________________________________________________________________
        //
        //
        //! Inner node
        //
        //______________________________________________________________________
        class Node : public Object
        {
        public:
            //__________________________________________________________________
            //
            // Definitions
            //__________________________________________________________________
            typedef CxxPoolOf<Node> Pool; //!< alias
            typedef CxxListOf<Node> List; //!< alias

            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________
            explicit Node() noexcept; //!< setup
            virtual ~Node() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            // Methods
            //__________________________________________________________________
            void     clear() noexcept; //!< clean hkey and data

            //__________________________________________________________________
            //
            // Members
            //__________________________________________________________________
            const size_t hkey; //!< Hash Key
            void * const data; //!< some data/key
            Node *       next; //!< for list/pool
            Node *       prev; //!< for list

        private:
            Y_Disable_Copy_And_Assign(Node); //!< discarding
        };

        typedef Node::List Slot; //!< alias

        //! data/key comparison
        typedef bool (*Same)(const void * const, const void * const);

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit HTable(const size_t=4); //!< setup with optional min slots
        virtual ~HTable() noexcept;      //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void free()    noexcept;
        virtual void release() noexcept;

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! search node
        /**
         \param hkey must have this key
         \param data for comparison
         \param same same(data,node->data) to test
         \param slot slot where it should be
         \return found node
         */
        const Node * search(const size_t       hkey,
                            const void * const data,
                            Same const         same,
                            const Slot *   &   slot) const;

        //! search node with pre-fetching
        /**
         \param hkey must have this key
         \param data for comparison
         \param same same(data,node->data) to test
         \param slot slot where it should be
         \return found node
         */
        Node *       search(const size_t       hkey,
                            const void * const data,
                            Same const         same,
                            Slot *   &         slot);

        //! hkey/data insertion
        /**
         \param hkey hash key
         \param data data/key
         \param same same(data,node->data) to test
         \return inserted node, NULL on failure
         */
        Node * insert(const size_t hkey,
                      void * const data,
                      Same const   same);

        //! remove found node
        void remove(Node * const ) noexcept;

        //! try to remove data
        /**
         \param hkey hash key
         \param data data/key
         \param same same(data,node->data) to test
         \return true if found and removed
         */
        void * remove(const size_t       hkey,
                      const void * const data,
                      Same const         same);



        const size_t    size; //!< keep inserted count
    private:
        class Code;
        Y_Disable_Copy_And_Assign(HTable); //!< discarding
        Code *          code; //!< inner code
        CxxPoolOf<Node> pool; //!< pool
    };

}

#endif

