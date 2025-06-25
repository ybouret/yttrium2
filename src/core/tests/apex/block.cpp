#include "y/apex/m/archon.hpp"
#include "y/calculus/alignment.hpp"
#include "y/core/utils.hpp"
#include "y/hexadecimal.hpp"
#include "y/object.hpp"
#include "y/apex/metrics.hpp"
#include "y/calculus/bits-for.hpp"
#include "y/type/sign.hpp"

#include <iostream>
#include <iomanip>
#include <cstring>

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

        template <ViewType VIEW>
        struct UnsignedFor;

        template <> struct UnsignedFor<View8>  { typedef uint8_t  Type; };
        template <> struct UnsignedFor<View16> { typedef uint16_t Type; };
        template <> struct UnsignedFor<View32> { typedef uint32_t Type; };
        template <> struct UnsignedFor<View64> { typedef uint64_t Type; };





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

            friend std::ostream & operator<<(std::ostream &os, const BlockAPI &self)
            {
                return self.print(os);
            }

            virtual size_t update(BlockAPI * const []) noexcept = 0;
            virtual void   resize(const size_t numBits) noexcept = 0;

#if 0
            size_t upgrade() noexcept
            {
                zeroPad();
                return update();
            }
#endif

            size_t         size;
            const size_t   maxi;
            const ViewType view;

        private:
            Y_Disable_Copy_And_Assign(BlockAPI);
            virtual bool doCheck() const noexcept = 0;
            virtual void zeroPad()       noexcept = 0;
            virtual std::ostream & print(std::ostream&) const = 0;

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

            static inline size_t  SizeFor(const size_t numBits) noexcept
            {
                return Alignment::On<UnitBits>::Ceil(numBits) / UnitBits;
            }

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


            inline  void adjust() noexcept
            {
                while( (size>0) && (0 == data[size-1]) )
                    --size;
                assert(isValid());
            }

            virtual size_t update(BlockAPI * const sync[]) noexcept
            {
                assert(0!=sync);
                adjust();
                const size_t numBits = bits();
                assert(0!=sync[0]); sync[0]->resize(numBits);
                assert(0!=sync[1]); sync[1]->resize(numBits);
                assert(0!=sync[2]); sync[2]->resize(numBits);
                return numBits;
            }

            virtual void resize(const size_t numBits) noexcept
            {
                size = SizeFor(numBits);
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
                if(size>0) Y_Block_Check(0!=data[size-1]);
                for(size_t i=size;i<maxi;++i) Y_Block_Check(0==data[i]);
                return true;
            }

            inline virtual std::ostream & print(std::ostream &os) const
            {
                os << "@." << std::setw(2) << UnitBits << '[';
                size_t i=size;
                while(i-- > 0)
                    os << ' ' << Hexadecimal(data[i]);
                os << ' ' << ']' << '#' << size;
                return os;
            }
        };

        struct Transmogrify
        {
            template <typename SMALL, typename LARGE> static inline
            void Expand(Block<SMALL> &target, const Block<LARGE> &source) noexcept
            {
                assert(source.isValid());
                static const unsigned RHO = sizeof(LARGE)/sizeof(SMALL);
                static const unsigned SHR = sizeof(SMALL) * 8;
                SMALL *      small = target.data;
                const LARGE *large = source.data;
                for(size_t i=source.size;i>0;--i)
                {
                    const LARGE value = *(large++);
                    for(unsigned j=0;j<RHO;++j)
                    {
                        *(small++) = SMALL(value>>(j*SHR));
                    }
                }
                //target.size = source.size * RHO;
                //target.adjust();
            }

            template <typename LARGE, typename SMALL> static inline
            void Shrink(Block<LARGE> &target, const Block<SMALL> &source) noexcept
            {
                assert(source.isValid());
                static const unsigned RHO = sizeof(LARGE)/sizeof(SMALL);
                static const unsigned SHL = sizeof(SMALL) * 8;

                const size_t words = source.size;
                const SMALL *small = source.data;
                LARGE       *large = target.data;
                for(size_t i = (target.size = Alignment::To<LARGE>::Ceil(words*sizeof(SMALL))/sizeof(LARGE)), used=0;i>0;--i)
                {
                    LARGE value = *(small++); ++used;
                    for(unsigned j=1;j<RHO;++j)
                    {
                        const LARGE temp = *(small++);
                        value |= (temp << (j*SHL));
                        if(++used>=words) break;
                    }
                    *(large++) = value;
                    if(used>=words) break;
                }
                //assert(target.isValid());
            }


            template <typename SMALL, typename LARGE> static inline
            void To(Block<SMALL> &target, const Block<LARGE> &source, const IntToType<Negative> &) noexcept
            {
                Expand(target,source);
            }

            template <typename LARGE, typename SMALL> static inline
            void To(Block<LARGE> &target, const Block<SMALL> &source, const IntToType<Positive> &) noexcept
            {
                Shrink(target,source);
            }

            template <typename T> static inline
            void To(Block<T> &, const Block<T> &, const IntToType<__Zero__> &) noexcept
            {

            }

            template <typename TARGET, typename SOURCE> static inline
            void To(Block<TARGET> &target, const Block<SOURCE> &source) noexcept
            {
                static const unsigned         TSize = sizeof(TARGET);
                static const unsigned         SSize = sizeof(SOURCE);
                static const SignType         Which = (TSize < SSize) ? Negative : (SSize<TSize ? Positive : __Zero__);
                static const IntToType<Which> choice = {};
                To(target,source,choice);
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
            sync(),
            wksp(),
            dataShift(0),
            dataBytes( Metrics::BytesFor(userBytes,dataShift) ),
            dataEntry( Query(dataShift) )
            {
                setup();
            }

            Blocks(const Blocks &other) :
            base(0),
            sync(),
            wksp(),
            dataShift(0),
            dataBytes( Metrics::BytesFor(other.block<uint8_t>().size,dataShift) ),
            dataEntry( Query(dataShift) )
            {
                setup();
                const size_t toCopy =
                block<uint8_t>() .size = other.block<uint8_t>() .size;
                block<uint16_t>().size = other.block<uint16_t>().size;
                block<uint32_t>().size = other.block<uint32_t>().size;
                block<uint64_t>().size = other.block<uint64_t>().size;
                memcpy(dataEntry,other.dataEntry,toCopy);
            }



            template <typename T> inline
            Block<T>  & block() noexcept
            { return *(Block<T> *) &base[BlockProtoSize*IntegerLog2For<T>::Value]; }

            template <typename T> inline
            const Block<T>  & block() const noexcept
            { return *(Block<T> *) &base[BlockProtoSize*IntegerLog2For<T>::Value]; }

            virtual ~Blocks() noexcept
            {
                static Archon &archon = Archon::Location();
                archon.store(dataShift,dataEntry);
            }


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

            void setup() noexcept
            {
                // base address
                Coerce(base) = static_cast<uint8_t *>( Y_Memory_BZero(wksp) );

                {
                    // dress up blocks
                    new (base)                  Block<uint8_t>(  dataEntry, dataBytes     );
                    new (base+  BlockProtoSize) Block<uint16_t>( dataEntry, dataBytes >> 1);
                    new (base+2*BlockProtoSize) Block<uint32_t>( dataEntry, dataBytes >> 2);
                    new (base+3*BlockProtoSize) Block<uint64_t>( dataEntry, dataBytes >> 3);
                }

                {
                    // record sync
                    Block<uint8_t>  & b8  = block<uint8_t>();
                    Block<uint16_t> & b16 = block<uint16_t>();
                    Block<uint32_t> & b32 = block<uint32_t>();
                    Block<uint64_t> & b64 = block<uint64_t>();

                    Coerce(sync[0][0]) = &b16; Coerce(sync[0][1]) = &b32; Coerce(sync[0][2]) = &b64;
                    Coerce(sync[1][0]) = &b8;  Coerce(sync[1][1]) = &b32; Coerce(sync[1][2]) = &b64;
                    Coerce(sync[2][0]) = &b8;  Coerce(sync[2][1]) = &b16; Coerce(sync[2][2]) = &b64;
                    Coerce(sync[3][0]) = &b8;  Coerce(sync[3][1]) = &b16; Coerce(sync[3][2]) = &b32;
                }
            }

            static void * Query(const unsigned shift)
            {
                static Archon &archon = Archon::Instance();
                return archon.query(shift);
            }

        };


        class Model : public Object, private Blocks
        {
        public:
            typedef void (Model:: *Change)();

            explicit Model(const size_t   userBytes,
                           const ViewType userView) :
            Object(),
            Blocks(userBytes),
            view(userView),
            bytes(block<uint8_t>().size),
            bits(0)
            {

            }

            explicit Model(const Model &  userModel,
                           const ViewType userView) :
            Object(),
            Blocks( userModel ),
            view(   userModel.view ),
            bytes(block<uint8_t>().size),
            bits(0)
            {
                assert( bytes == userModel.bytes );
                set(userView);
            }

            virtual ~Model() noexcept
            {
            }


            void set(const ViewType vtgt) noexcept
            {
                Change const meth = ChangeTo[vtgt][view];
                (*this.*meth)();
                Coerce(view) = vtgt;
            }

            void update() noexcept
            {
                switch( view )
                {
                    case View8:  block<uint8_t>(). update(sync[0]); break;
                    case View16: block<uint16_t>().update(sync[1]); break;
                    case View32: block<uint32_t>().update(sync[2]); break;
                    case View64: block<uint64_t>().update(sync[3]); break;
                }
            }


            template <typename T>
            inline const Block<T> & get() const noexcept
            {
                assert( BlockAPI::VTable[ IntegerLog2For<T>::Value ] == view );
                return block<T>();
            }


            template <typename T>
            inline  Block<T> & get() noexcept
            {
                assert( BlockAPI::VTable[ IntegerLog2For<T>::Value ] == view );
                return block<T>();
            }

            template <typename T>
            inline  Block<T> & make() noexcept
            {
                set(  BlockAPI::VTable[ IntegerLog2For<T>::Value ] );
                return block<T>();
            }


            const ViewType view;
            const size_t  &bytes;
            const size_t   bits;

        private:
            Y_Disable_Copy_And_Assign(Model);
            static Change const ChangeTo[Metrics::Views][Metrics::Views];

            template <typename TARGET, typename SOURCE>
            inline void To() noexcept {
                assert( BlockAPI::VTable[ IntegerLog2For<SOURCE>::Value ] == view );
                Transmogrify::To( block<TARGET>(), block<SOURCE>() );
            }

        };

#define Y_APM_(TARGET,SOURCE) & Model::To<uint##TARGET##_t,uint##SOURCE##_t>
#define Y_APM(TARGET) { Y_APM_(TARGET,8), Y_APM_(TARGET,16), Y_APM_(TARGET,32), Y_APM_(TARGET,64) }

        Model::Change const Model:: ChangeTo[Metrics::Views][Metrics::Views] =
        {
            Y_APM(8), Y_APM(16), Y_APM(32), Y_APM(64)
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



    Y_CHECK( sizeof( Apex::Block<uint8_t> ) == sizeof( Apex::Block<uint16_t>) );
    Y_CHECK( sizeof( Apex::Block<uint8_t> ) == sizeof( Apex::Block<uint32_t>) );
    Y_CHECK( sizeof( Apex::Block<uint8_t> ) == sizeof( Apex::Block<uint64_t>) );

    Y_PRINTV( Apex::Blocks::BlockProtoSize );
    Y_SIZEOF( Apex::Blocks );

    const uint64_t p64[2] = { 0xabdc, 0x1234 };
    {
        Apex::Blocks b(0);

        Apex::Block<uint64_t> &b64 = b.block<uint64_t>();
        b64.data[0] = p64[0];
        b64.data[1] = p64[1];
        b64.size    = 2;
        Y_ASSERT(b64.isValid());
        const size_t numBits = b64.update(b.sync[3]);
        std::cerr << "numBits=" << numBits << std::endl;

        Apex::Block<uint32_t> &b32 = b.block<uint32_t>();
        Apex::Block<uint16_t> &b16 = b.block<uint16_t>();
        Apex::Block<uint8_t>  &b8  = b.block<uint8_t>();

        std::cerr << "#64 = " << b64.size << std::endl;
        std::cerr << "#32 = " << b32.size << std::endl;
        std::cerr << "#16 = " << b16.size << std::endl;
        std::cerr << "#8  = " << b8.size << std::endl;


        std::cerr << "I/O with 64 bits" << std::endl;
        std::cerr << b64 << std::endl;
        Apex::Transmogrify::To(b32,b64);
        std::cerr << b32 << std::endl;
        Apex::Transmogrify::To(b64,b32);
        std::cerr << b64 << std::endl; Y_ASSERT( 0 == memcmp(b64.data,p64,sizeof(p64)));

        Apex::Transmogrify::To(b16,b64);
        std::cerr << b16 << std::endl;
        Apex::Transmogrify::To(b64,b16);
        std::cerr << b64 << std::endl; Y_ASSERT( 0 == memcmp(b64.data,p64,sizeof(p64)));

        Apex::Transmogrify::To(b8,b64);
        std::cerr << b8 << std::endl;
        Apex::Transmogrify::To(b64,b8);
        std::cerr << b64 << std::endl; Y_ASSERT( 0 == memcmp(b64.data,p64,sizeof(p64)));

        std::cerr << "I/O with 32 bits" << std::endl;
        Apex::Transmogrify::To(b32,b64);
        uint32_t p32[4] = { 0 };
        memcpy(p32,b32.data,sizeof(p32));
        Apex::Transmogrify::To(b16,b32);
        std::cerr << b16 << std::endl;
        Apex::Transmogrify::To(b32,b16);
        std::cerr << b32 << std::endl; Y_ASSERT( 0 == memcmp(b32.data,p32,sizeof(p32)));

        Apex::Transmogrify::To(b8,b32);
        std::cerr << b8 << std::endl;
        Apex::Transmogrify::To(b32,b8);
        std::cerr << b32 << std::endl; Y_ASSERT( 0 == memcmp(b32.data,p32,sizeof(p32)));


        std::cerr << "I/O with 16 bits" << std::endl;
        Apex::Transmogrify::To(b16,b32);
        uint16_t p16[8] = { 0 };
        memcpy(p16,b16.data,sizeof(p16));
        Apex::Transmogrify::To(b8,b16);
        std::cerr << b8 << std::endl;
        Apex::Transmogrify::To(b16,b8);
        std::cerr << b16 << std::endl; Y_ASSERT( 0 == memcmp(b16.data,p16,sizeof(p16)));
    }


    {
        std::cerr << "Using Models" << std::endl;
        Apex::Model m(10,Apex::View64);


        m.get<uint64_t>().data[0] = p64[0];
        m.get<uint64_t>().data[1] = p64[1];
        m.get<uint64_t>().size    = 2;
        m.update();

        Y_ASSERT(m.get<uint64_t>().isValid());

        std::cerr << "Printing..." << std::endl;
        std::cerr << m.make<uint64_t>() << std::endl;
        std::cerr << m.make<uint32_t>() << std::endl;
        std::cerr << m.make<uint16_t>() << std::endl;
        std::cerr << m.make<uint8_t>() << std::endl;

    }

}
Y_UDONE()

