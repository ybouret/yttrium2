#include "y/apex/m/archon.hpp"
#include "y/calculus/alignment.hpp"
#include "y/core/utils.hpp"
#include "y/hexadecimal.hpp"
#include "y/object.hpp"
#include "y/apex/metrics.hpp"
#include "y/calculus/bits-for.hpp"

#include <iostream>

namespace Yttrium
{
    namespace Apex
    {


        enum ViewType
        {
            View8,
            View16,
            View32,
            View64
        };



#define Y_Block_Check(EXPR) do { \
if ( !(EXPR) ) { std::cerr << #EXPR << " failure" << std::endl; return false; } \
} while(false)


        class BlockAPI
        {
        public:
            static const ViewType VTable[Metrics::Views];

            explicit BlockAPI(const size_t   n,
                              const ViewType v) :
            size(0),
            maxi(n),
            view(v)
            {
            }

            virtual ~BlockAPI() noexcept
            {

            }

            bool isValid() const noexcept
            {
                Y_Block_Check(size<=maxi);
                return doCheck();
            }


            virtual size_t update() noexcept = 0;

            size_t upgrade() noexcept
            {
                zeroPad();
                return update();
            }

            size_t         size;
            const size_t   maxi;
            const ViewType view;

        private:
            Y_Disable_Copy_And_Assign(BlockAPI);
            virtual bool doCheck() const noexcept = 0;
            virtual void zeroPad()       noexcept = 0;
        };

        const ViewType BlockAPI::VTable[] =
        {
            View8, View16, View32, View64
        };


        template <typename T>
        class Block : public BlockAPI
        {
        public:
            static const ViewType View = ViewType( IntegerLog2For<T>::Value );
            static const unsigned UnitSize = sizeof(T);
            static const unsigned UnitBits = 8 * UnitSize;

            explicit Block(void * const entry,
                           const size_t count) noexcept :
            BlockAPI(count,View),
            data( static_cast<T*>(entry) )
            {
                assert(0!=data);
                std::cerr << "Block" << view <<  " : #" << maxi << std::endl;
            }

            virtual ~Block() noexcept
            {
            }

            size_t bits() const noexcept
            {
                if(size<=0) return 0;
                const size_t msw = size-1;
                assert(0!=data[msw]);
                return msw * UnitBits + Calculus::BitsFor::Count(data[msw]);
            }

            virtual size_t update() noexcept
            {
                while( (size>0) && (0 == data[size-1]) )
                    --size;
                assert(isValid());
                return bits();
            }

            T * const data;
        private:
            Y_Disable_Copy_And_Assign(Block);


            virtual void zeroPad() noexcept {
                memset(data+size,0,(maxi-size) * sizeof(T));
            }

            inline virtual bool doCheck() const noexcept
            {
                assert(size<=maxi);
                if(size>0) Y_Block_Check(0==data[size-1]);
                for(size_t i=size;i<maxi;++i) Y_Block_Check(0==data[i]);
                return true;
            }
        };

        class Blocks
        {
        public:
            typedef Block<uint8_t> BlockProto;
            static const size_t    BlockProtoSize = sizeof(BlockProto);
            static const size_t    NumBlocks      = Metrics::Views;

            explicit Blocks(const size_t userBytes) :
            base(0),
            wksp(),
            dataShift(0),
            dataBytes( Metrics::BytesFor(userBytes,dataShift) ),
            dataEntry( Query(dataShift) )
            {
                Coerce(base) = static_cast<uint8_t *>( Y_Memory_BZero(wksp) );
                new (base)                  Block<uint8_t>(  dataEntry, dataBytes     );
                new (base+  BlockProtoSize) Block<uint16_t>( dataEntry, dataBytes >> 1);
                new (base+2*BlockProtoSize) Block<uint32_t>( dataEntry, dataBytes >> 2);
                new (base+3*BlockProtoSize) Block<uint64_t>( dataEntry, dataBytes >> 3);
            }

            template <typename T> inline
            Block<T>  & block() noexcept { return * static_cast<Block<T> *>( &base[BlockProtoSize*IntegerLog2For<T>::Value]); }

            virtual ~Blocks() noexcept
            {
                static Archon &archon = Archon::Location();
                archon.store(dataShift,dataEntry);
            }


        private:
            Y_Disable_Copy_And_Assign(Blocks);
            uint8_t * const base;
            void *          wksp[ Alignment::WordsGEQ<NumBlocks*BlockProtoSize>::Count ];
            unsigned        dataShift;
            size_t          dataBytes;
            void *   const  dataEntry;

            template <typename T> inline
            void * getBlockAddr() const noexcept {
                return &base[BlockProtoSize*IntegerLog2For<T>::Value];
            }


            static void * Query(const unsigned shift)
            {
                static Archon &archon = Archon::Instance();
                return archon.query(shift);
            }

        };




#if 0
        template <size_t LN2> struct UnsignedForLn2;
        template <> struct UnsignedForLn2<0> { typedef uint8_t  Type; };
        template <> struct UnsignedForLn2<1> { typedef uint16_t Type; };
        template <> struct UnsignedForLn2<2> { typedef uint32_t Type; };
        template <> struct UnsignedForLn2<3> { typedef uint64_t Type; };




#define Y_Block_Check(EXPR) do { \
if ( !(EXPR) ) { std::cerr << #EXPR << " failure" << std::endl; return false; } \
} while(false)

        class BlockAPI
        {
        public:
            explicit BlockAPI(const size_t n) :
            size(0),
            capacity(n)
            {
            }

            virtual ~BlockAPI() noexcept
            {

            }

            friend std::ostream & operator<<(std::ostream &os, const BlockAPI &self)
            {
                return self.print(os);
            }

            virtual void update()  noexcept = 0;
            virtual void upgrade() noexcept = 0;

            bool isValid() const noexcept
            {
                Y_Block_Check(size<=capacity);
                return checkData();
            }

            size_t       size;
            const size_t capacity;

        private:
            Y_Disable_Copy_And_Assign(BlockAPI);
            virtual bool            checkData()  const noexcept = 0;
            virtual std::ostream &  print(std::ostream &) const = 0;
        };

        template <typename T>
        class Block : public BlockAPI
        {
        public:
            inline explicit Block(void * const entry,
                                  const size_t count) noexcept :
            BlockAPI(count),
            data( static_cast<T*>(entry) )
            {
                assert(capacity>0);
                assert(entry!=0);
                assert(Memory::Stealth::Are0(data,capacity*sizeof(T)));
            }

            inline virtual ~Block() noexcept
            {
            }

            virtual void upgrade() noexcept
            {
                assert(size<=capacity);
                for(size_t i=size;i<capacity;++i) data[i] = 0;
                update();
            }

            virtual void update() noexcept
            {
                assert(size<=capacity);
                while(size>0 && 0 == data[size-1]) --size;
                assert(isValid());
            }


            T * const data;

        private:
            Y_Disable_Copy_And_Assign(Block);
            virtual bool checkData() const noexcept
            {
                Y_Block_Check(data!=0);
                if(size>0) { Y_Block_Check(data[size-1]!=0); }
                Y_Block_Check(Memory::Stealth::Are0(data+size,(capacity-size)*sizeof(T)));
                return true;
            }

            virtual std::ostream & print(std::ostream &os) const
            {
                os << '[';
                size_t i=size;
                while(i-- > 0)
                    os << ' ' << Hexadecimal(data[i]);
                //return Hexadecimal::Display(os,data,size);

                return os << ' ' <<  ']';
            }

        };

        struct Convert
        {
            template <typename SMALL, typename LARGE> static inline
            void Expand(Block<SMALL> &target, const Block<LARGE> &source)
            {
                assert( source.isValid() );
                assert( target.isValid() );

                static const unsigned shr  = sizeof(SMALL) << 3;
                static const unsigned loop = sizeof(LARGE)/sizeof(SMALL);
                SMALL *       tgt = target.data;
                const LARGE * src = source.data;
                for(size_t i=source.size;i>0;--i)
                {
                    const LARGE value = *(src++);
                    for(size_t j=0;j<loop;++j)
                        *(tgt++) = SMALL( value >> (shr*j) );
                }
                target.size = source.size * loop;
                target.upgrade();
            }

            template <typename LARGE, typename SMALL> static inline
            void Shrink(Block<LARGE> &target, const Block<SMALL> &source)
            {
                assert( source.isValid() );
                assert( target.isValid() );
                static const unsigned shl  = sizeof(SMALL) << 3;
                static const unsigned loop = sizeof(LARGE)/sizeof(SMALL);
                LARGE *       tgt = target.data;
                const SMALL * src = source.data;
                const size_t  size = source.size;
                for(size_t i= (target.size = Alignment::To<LARGE>::Ceil(size)/sizeof(LARGE)),used=0;i>0;--i)
                {
                    LARGE value = *(src++); ++used;
                    for(size_t j=1;j<loop;++j)
                    {
                        const LARGE temp = *(src++); ++used;
                        value |= (temp << (j*shl));
                        if(used>=size) break;
                    }
                    *(tgt++) = value;
                    if(used>=size) break;
                }
                target.upgrade();
            }

            template <typename LHS, typename RHS> static inline
            void To(Block<LHS> &lhs, const Block<RHS> &rhs) noexcept
            {
                static const IntToType< sizeof(LHS)< sizeof(RHS) > choice = {};
                To(lhs,rhs,choice);
            }

            template <typename LHS, typename RHS> static inline
            void To(Block<LHS> &lhs, const Block<RHS> &rhs, const IntToType<true> &) noexcept
            {
                Expand(lhs,rhs);
            }

            template <typename LHS, typename RHS> static inline
            void To(Block<LHS> &lhs, const Block<RHS> &rhs, const IntToType<false> &) noexcept
            {
                Shrink(lhs,rhs);
            }


        };




        class Blocks
        {
        public:
            typedef Block<uint8_t> BlockProto;
            static const size_t    BlockProtoSize   = sizeof(BlockProto);
            static const size_t    NumBlocks        = Metrics::WordShift + 1;
            static const size_t    MinBytesPerBlock = Metrics::WordBytes;


            explicit Blocks(size_t bytesPerBlock) :
            base(0),
            wksp(),
            shift(0),
            count( Metrics::BytesFor( MaxOf(bytesPerBlock,MinBytesPerBlock) * NumBlocks,shift) ),
            entry( Query(shift) )
            {
                assert(count/NumBlocks>=bytesPerBlock);
                bytesPerBlock = count/NumBlocks;
                Coerce(base) = static_cast<uint8_t *>(Y_Memory_BZero(wksp));
                {
                    uint8_t * p = entry;
                    new ( addrFor<uint8_t>() )  Block<uint8_t>(p,bytesPerBlock);                   p+=bytesPerBlock;
                    new ( addrFor<uint16_t>() ) Block<uint16_t>(p,bytesPerBlock/sizeof(uint16_t)); p+=bytesPerBlock;
                    new ( addrFor<uint32_t>() ) Block<uint32_t>(p,bytesPerBlock/sizeof(uint32_t)); p+=bytesPerBlock;
                    new ( addrFor<uint64_t>() ) Block<uint64_t>(p,bytesPerBlock/sizeof(uint64_t)); p+=bytesPerBlock;
                }
            }

            template <typename T> inline
            Block<T> & block() noexcept
            {
                return *static_cast<Block<T> *>( addrFor<T>() );
            }

            template <typename T> inline
            const Block<T> & block() const noexcept
            {
                return *static_cast<const Block<T> *>( addrFor<T>() );
            }

            virtual ~Blocks() noexcept
            {
                static Archon &archon = Archon::Location();
                archon.store(shift,entry);
            }

        private:
            Y_Disable_Copy_And_Assign(Blocks);
            uint8_t * const base;
            void *          wksp[ Alignment::WordsGEQ< NumBlocks * sizeof(Block<uint8_t>) >::Count ];
            unsigned        shift;
            const size_t    count;
            uint8_t * const entry;

            template <typename T> inline
            void * addrFor() const noexcept
            {
                return (void*)( base + IntegerLog2For<T>::Value * BlockProtoSize);
            }

            static  uint8_t * Query(const unsigned userShift)
            {
                static Archon &archon = Archon::Instance();
                return static_cast<uint8_t *>( archon.query(userShift) );
            }
        };

        class Model : public Object, public Blocks
        {
        public:
            explicit Model(const size_t bytesPerBlock) :
            Object(),
            Blocks( bytesPerBlock ),
            bytes( block<uint8_t>().size ),
            bits(0)
            {
            }

            virtual ~Model() noexcept {}

            const size_t & bytes;
            size_t         bits;

        private:
            Y_Disable_Copy_And_Assign(Model);

        };
#endif

    }
}

#include "y/utest/run.hpp"
#include "y/system/rand.hpp"

using namespace Yttrium;

namespace
{
    struct Blk
    {
        unsigned shift;
        void *   entry;
    };

    static const size_t MaxBlk = 30;
    static Blk          Blks[MaxBlk];
}

Y_UTEST(apex_block)
{
    System::Rand ran;

    Y_PRINTV(Apex::Archon::NumShifts);

    Apex::Archon & mgr = Apex::Archon::Instance();


    if(true)
    {
        mgr.display(std::cerr,0);
        Y_Memory_BZero(Blks);
        for(size_t i=0;i<MaxBlk;++i)
        {
            Blk &b  = Blks[i];
            while( (b.shift = unsigned(ran.in(20)) ) < Apex::Archon::MinShift )
                ;
            b.entry = mgr.query(b.shift);
        }
        ran.shuffle(Blks,MaxBlk);

        mgr.display(std::cerr,0);

        for(size_t i=0;i<MaxBlk;++i)
        {
            Blk &b  = Blks[i];
            mgr.store(b.shift,b.entry);
        }
        mgr.display(std::cerr,0);
    }



    Y_CHECK( sizeof( Apex::Block<uint8_t> ) == sizeof( Apex::Block<uint16_t>) );
    Y_CHECK( sizeof( Apex::Block<uint8_t> ) == sizeof( Apex::Block<uint32_t>) );
    Y_CHECK( sizeof( Apex::Block<uint8_t> ) == sizeof( Apex::Block<uint64_t>) );

    Y_PRINTV( Apex::Blocks::BlockProtoSize );
    Y_SIZEOF( Apex::Blocks );
    {
        Apex::Blocks b(0);
    }

}
Y_UDONE()

