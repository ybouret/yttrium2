
#include "y/apex/block/model.hpp"


namespace Yttrium
{
    namespace Apex
    {
        Model:: Model(const size_t   userBytes,
                      const ViewType userView) :
        Object(),
        Blocks(userBytes),
        view(userView),
        bytes(block<uint8_t>().size),
        bits(0)
        {

        }

        Model:: Model(const Model &  userModel,
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

        Model:: Model(const natural_t n) :
        Object(),
        Blocks( sizeof(n) ),
        view( View64 ),
        bytes(block<uint8_t>().size),
        bits(0)
        {
            Block<uint64_t> &b64 = block<uint64_t>();
            b64.size    = 1;
            b64.data[0] = n;
            update();
        }


        Model:: Model(const natural_t * const arr, const size_t num) :
        Object(),
        Blocks( sizeof(natural_t) * num ),
        view( View64 ),
        bytes(block<uint8_t>().size),
        bits(0)
        {
            Block<uint64_t> &b64 = block<uint64_t>();
            b64.size    = num;
            memcpy(b64.data,arr,num*sizeof(uint64_t));
            update();
        }

        unsigned Model:: BytesPerUnit(const ViewType v) noexcept
        {
            static const unsigned one = 1;
            return one << unsigned(v);
        }

        namespace
        {
            template <typename T> static inline
            void BlockCopy(T *                target,
                           const void * const source,
                           size_t             length) noexcept
            {
                assert(Good(target,length));
                assert(Good(source,length));
                const T * C = (const T *)source;
                while(length-- > 0)
                    *(target++) = *(C++);
            }

        }


        Model:: Model(const void * const entry,
                      const size_t       count,
                      const ViewType     tview) :
        Object(),
        Blocks(  count * BytesPerUnit(tview)  ),
        view( tview ),
        bytes(block<uint8_t>().size),
        bits(0)
        {
            assert( Good(entry,count) );
            switch(view)
            {
                case View8:  BlockCopy( block<uint8_t>().data,  entry, count); break;
                case View16: BlockCopy( block<uint16_t>().data, entry, count); break;
                case View32: BlockCopy( block<uint32_t>().data, entry, count); break;
                case View64: BlockCopy( block<uint64_t>().data, entry, count); break;
            }
            update();
        }



        Model:: ~Model() noexcept
        {
        }

        void Model:: set(const ViewType vtgt) noexcept
        {
            (*this.*ChangeTo[vtgt][view])();
            Coerce(view) = vtgt;
        }

        void Model:: ldz(const ViewType userType) noexcept
        {
            
        }


        void Model:: update() noexcept
        {
            Coerce(bits) =  (*this.*Updating[view])();
        }


#define Y_APM_(TARGET,SOURCE) & Model::To<uint##TARGET##_t,uint##SOURCE##_t>
#define Y_APM(TARGET) { Y_APM_(TARGET,8), Y_APM_(TARGET,16), Y_APM_(TARGET,32), Y_APM_(TARGET,64) }

        Model::Change const Model:: ChangeTo[Metrics::Views][Metrics::Views] =
        {
            Y_APM(8), Y_APM(16), Y_APM(32), Y_APM(64)
        };

        Model::Update const Model:: Updating[Metrics::Views] =
        {
            & Model::Go<uint8_t>, & Model::Go<uint16_t>, & Model::Go<uint32_t>, & Model::Go<uint64_t>
        };

        
        std::ostream & operator<<(std::ostream &os, const Model &self)
        {
            switch(self.view)
            {
                case View8:  os << self.block<uint8_t>();  break;
                case View16: os << self.block<uint16_t>(); break;
                case View32: os << self.block<uint32_t>(); break;
                case View64: os << self.block<uint64_t>(); break;
            }
            if(View8!=self.view)
                os << ":byte" << ASCII::Plural::s(self.bytes) << "=" << self.bytes;
            os     << ":bit"  << ASCII::Plural::s(self.bits)  << "=" << self.bits;
            return os;
        }
    }

}

#include "y/stream/output.hpp"


namespace Yttrium
{
    namespace Apex
    {

        size_t Model:: save(OutputStream &fp)
        {
            const Block<uint8_t> &b = make<uint8_t>();
            size_t res = fp.emitVBR(b.size);
            fp.frame(b.data,b.size);
            return res + b.size;
        }
    }

}


#include "y/stream/input.hpp"
#include "y/pointer/auto.hpp"


namespace Yttrium
{
    namespace Apex
    {

        Model * Model:: Load(InputStream &fp, const ViewType userView)
        {
            const size_t   numBytes = fp.readVBR<size_t>();
            AutoPtr<Model> result   = new Model(numBytes,View8);

        }
    }

}
