
#include "y/apex/natural.hpp"
#include "y/apex/block/model.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace Apex
    {
        OpsMode Natural::Ops = Ops32_64;

        Natural:: Natural() : Number(),
        code( new Model(0, Model::SmallView[Ops]) )
        {
        }

        Natural:: ~Natural() noexcept
        {
            Destroy(code);
        }


        static inline size_t saveModel(Model &m, OutputStream &fp)
        {
            return m.save(fp);
        }

        size_t Natural:: serialize(OutputStream &fp) const
        {
            assert(0!=code);
            if(View8==code->view)
            {
                return saveModel(*code,fp);
            }
            else
            {
                Model::Pointer m(*code,View8);
                return saveModel(*m,fp);
            }
        }

        Natural:: Natural(const Natural &other) :
        Number(),
        code( new Model(*other.code,Model::SmallView[Ops]) )
        {

        }

        Natural & Natural:: operator=(const Natural &other)
        {

            if(this != &other)
            {
                
            }
            return *this;
        }



    }
    
}
