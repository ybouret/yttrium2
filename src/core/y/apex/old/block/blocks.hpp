
//! \file

#ifndef Y_Apex_Blocks_Included
#define Y_Apex_Blocks_Included 1

#include "y/apex/block/block.hpp"


namespace Yttrium
{
    namespace Apex
    {
        //______________________________________________________________________
        //
        //
        //
        //! Blocks of different views
        //
        //
        //______________________________________________________________________
        class Blocks
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Block<uint8_t> BlockProto;                          //!< alias
            static const size_t    BlockProtoSize = sizeof(BlockProto); //!< alias
            static const size_t    NumBlocks      = Metrics::Views;     //!< alias
            static const size_t    WorkspaceWords = Alignment::WordsGEQ<NumBlocks*BlockProtoSize>::Count; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! create blocks to hold given memory
            /**
             \param userBytes minimal bytes, will be aligned
             */
            explicit Blocks(const size_t userBytes);

            //! duplicate blocks
            /**
             allocate memory and copy data
             \param other source blocks
             */
            Blocks(const Blocks &other);

            //! cleanup
            virtual ~Blocks() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return reference to in-situ block
            template <typename T> inline
            Block<T>  & block() noexcept
            { return *(Block<T> *) &base[BlockProtoSize*IntegerLog2For<T>::Value]; }

            //! \return const reference to in-situ block
            template <typename T> inline
            const Block<T>  & block() const noexcept
            { return *(Block<T> *) &base[BlockProtoSize*IntegerLog2For<T>::Value]; }


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
        private:
            uint8_t * const  base; //!< workspace
        public:
            BlockAPI * const sync[ Metrics::Views ][3]; //!< foreign blocks to sync
        private:
            void *           wksp[ WorkspaceWords ];    //!< in-situ blocks
            unsigned         dataShift;                 //!< to hold bytes
            size_t           dataBytes;                 //!< 2^dataShift
            void *   const   dataEntry;                 //!< from Archin

            Y_Disable_Assign(Blocks);        //!< discarding
            void          setup() noexcept;  //!< format blocks

            //! query memory
            /**
             \param shift precomputed shift
             \return 2^shift bytes from archon
             */
            static void * Query(const unsigned shift);
        };


    }

}

#endif

