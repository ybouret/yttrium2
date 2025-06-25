
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

        Model:: ~Model() noexcept
        {
        }

        void Model:: set(const ViewType vtgt) noexcept
        {
            (*this.*ChangeTo[vtgt][view])();
            Coerce(view) = vtgt;
        }


        void Model:: update() noexcept
        {
            switch( view )
            {
                case View8:  block<uint8_t>(). update(sync[0]); break;
                case View16: block<uint16_t>().update(sync[1]); break;
                case View32: block<uint32_t>().update(sync[2]); break;
                case View64: block<uint64_t>().update(sync[3]); break;
            }
        }


#define Y_APM_(TARGET,SOURCE) & Model::To<uint##TARGET##_t,uint##SOURCE##_t>
#define Y_APM(TARGET) { Y_APM_(TARGET,8), Y_APM_(TARGET,16), Y_APM_(TARGET,32), Y_APM_(TARGET,64) }

        Model::Change const Model:: ChangeTo[Metrics::Views][Metrics::Views] =
        {
            Y_APM(8), Y_APM(16), Y_APM(32), Y_APM(64)
        };


    }

}

