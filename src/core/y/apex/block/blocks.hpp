
//! \file

#ifndef Y_Apex_Blocks_Included
#define Y_Apex_Blocks_Included 1

#include "y/apex/block/block.hpp"


namespace Yttrium
{
    namespace Apex
    {
        class Blocks
        {
        public:
            typedef Block<uint8_t> BlockProto;
            static const size_t    BlockProtoSize = sizeof(BlockProto);
            static const size_t    NumBlocks      = Metrics::Views;

            explicit Blocks(const size_t userBytes);
            Blocks(const Blocks &other);

            template <typename T> inline
            Block<T>  & block() noexcept
            { return *(Block<T> *) &base[BlockProtoSize*IntegerLog2For<T>::Value]; }

            template <typename T> inline
            const Block<T>  & block() const noexcept
            { return *(Block<T> *) &base[BlockProtoSize*IntegerLog2For<T>::Value]; }

            virtual ~Blocks() noexcept;

            void zset() noexcept;

        private:
            Y_Disable_Assign(Blocks);
            uint8_t * const  base;
        public:
            BlockAPI * const sync[ Metrics::Views ][3];
        private:
            void *           wksp[ Alignment::WordsGEQ<NumBlocks*BlockProtoSize>::Count ];
            unsigned         dataShift;
            size_t           dataBytes;
            void *   const   dataEntry;

            void          setup() noexcept;
            static void * Query(const unsigned shift);
        };


    }

}

#endif

