#include "y/apex/m/archon.hpp"
#include "y/calculus/alignment.hpp"
#include "y/core/utils.hpp"
#include "y/hexadecimal.hpp"
#include "y/object.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Apex
    {

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

    Y_CHECK(sizeof(Apex::Block<uint8_t>) == sizeof(Apex::Block<uint16_t>));
    Y_CHECK(sizeof(Apex::Block<uint8_t>) == sizeof(Apex::Block<uint32_t>));
    Y_CHECK(sizeof(Apex::Block<uint8_t>) == sizeof(Apex::Block<uint64_t>));

    {
        Apex::Blocks            b(0);

        std::cerr << "capacities: " << std::endl;
        std::cerr << b.block<uint8_t>().capacity  << "#" <<  b.block<uint8_t>().size  << std::endl;
        std::cerr << b.block<uint16_t>().capacity << "#" <<  b.block<uint16_t>().size << std::endl;
        std::cerr << b.block<uint32_t>().capacity << "#" <<  b.block<uint32_t>().size << std::endl;
        std::cerr << b.block<uint64_t>().capacity << "#" <<  b.block<uint64_t>().size << std::endl;

        Apex::Block<uint64_t> & b64 = b.block<uint64_t>();
        Apex::Block<uint32_t> & b32 = b.block<uint32_t>();
        Apex::Block<uint16_t> & b16 = b.block<uint16_t>();
        Apex::Block<uint8_t>  & b8  = b.block<uint8_t>();


        b64.data[0] = 0x123456ULL;
        b64.size = 1;
        b64.update();
        std::cerr << b64 << std::endl;
        Apex::Convert::To(b32,b64);
        std::cerr << b32 << std::endl;
        Apex::Convert::To(b16,b64);
        std::cerr << b16 << std::endl;
        Apex::Convert::To(b8,b64);
        std::cerr << b8 << std::endl;


#if 0
        std::cerr << b32 << std::endl;
        Apex::Convert::Expand(b32,b64);
        std::cerr << b32 << std::endl;

        std::cerr << b16 << std::endl;
        Apex::Convert::Expand(b16,b64);
        std::cerr << b16 << std::endl;

        Apex::Convert::Expand(b8,b64);
        std::cerr << b8 << std::endl;

        Apex::Convert::Shrink(b16,b8);
        std::cerr << "b16=" << b16 << std::endl;
        Apex::Convert::Shrink(b32,b8);
        std::cerr << "b32=" << b32 << std::endl;
        Apex::Convert::Shrink(b64,b8);
        std::cerr << "b64=" << b64 << std::endl;
#endif

    }





}
Y_UDONE()

