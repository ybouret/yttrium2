#include "y/mkl/fit/samples.hpp"
#include "y/exception.hpp"
#include "y/core/utils.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            const char * const SamplesCommon:: CallSign = "Fit::Samples";
            
            SamplesCommon:: SamplesCommon() noexcept : vlist()
            {
                
            }


            SamplesCommon:: ~SamplesCommon() noexcept
            {
            }

            void SamplesCommon:: ErrorMultipleName(const String &id)
            {
                throw Specific::Exception(CallSign,"found multiple name '%s'", id.c_str());
            }

            bool SamplesCommon:: found(const Variable &var) const noexcept
            {
                for(const VNode *vn=vlist->head;vn;vn=vn->next)
                {
                    if( **vn == var ) return true;
                }
                return false;
            }

            void SamplesCommon:: collect(const Variables &vars)
            {
                for(Variables::ConstIterator it=vars->begin();it!=vars->end();++it)
                {
                    const Variable &var = **it; if(found(var)) continue;
                    vlist << var;
                }
            }

            size_t SamplesCommon:: width() const noexcept
            {
                size_t w = 0;
                for(VNode *vn=vlist->head;vn;vn=vn->next)
                    InSituMax(w, (**vn).global->name.size() );
                return w;
            }


        }

    }

}

