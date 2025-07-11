
//! \file

#ifndef Y_Cameo_FPointMultiplier_Included
#define Y_Cameo_FPointMultiplier_Included 1


#include "y/cameo/multiplier/api.hpp"
#include "y/cameo/multiplier/synod/fp-list.hpp"

namespace Yttrium
{

    namespace Cameo
    {

        template <typename T>
        class FPointMultiplier : public Multiplier<T>
        {
        public:
            Y_Args_Declare(T,Type);

            typedef Synod::FPList<T>              EngineType;
            typedef typename EngineType::UnitList UnitList;

            inline explicit FPointMultiplier(const size_t n=0) : Multiplier<T>(), engine()
            {
                engine.cache(n);
            }

            inline virtual ~FPointMultiplier() noexcept {
            }

            inline Caching *       operator->()       noexcept { return &engine; }
            inline const Caching * operator->() const noexcept { return &engine; }

            inline const UnitList & operator*() const noexcept { return *engine; }

            inline virtual void ld1() noexcept { engine.free(); }

            inline virtual T product()
            {
                return engine.product();
            }

        private:
            EngineType engine;

            virtual void mul(ParamType x)           { engine.push(x);   }
            virtual void mul(ParamType x, size_t n) { engine.push(x,n); }
        };
    }

}

#endif

