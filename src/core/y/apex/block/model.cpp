
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

        Model:: Model(const uint64_t n) :
        Object(),
        Blocks( sizeof(n) ),
        view( View64 ),
        bytes(block<uint8_t>().size),
        bits(0)
        {
            Block<uint64_t> &b64 = block<uint64_t>();
            b64.size    = 1;
            b64.data[0] = n;
            Coerce(bits) = update();
        }


        Model:: Model(const uint64_t * const arr, const size_t num) :
        Object(),
        Blocks( sizeof(uint64_t) * num ),
        view( View64 ),
        bytes(block<uint8_t>().size),
        bits(0)
        {
            Block<uint64_t> &b64 = block<uint64_t>();
            b64.size    = num;
            memcpy(b64.data,arr,num*sizeof(uint64_t));
            Coerce(bits) = update();
        }



        Model:: ~Model() noexcept
        {
        }

        void Model:: set(const ViewType vtgt) noexcept
        {
            (*this.*ChangeTo[vtgt][view])();
            Coerce(view) = vtgt;
        }


        size_t Model:: update() noexcept
        {
            return (*this.*Updating[view])();
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

