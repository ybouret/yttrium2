
//! \file

#ifndef Y_Cameo_FPointMultiplier_Included
#define Y_Cameo_FPointMultiplier_Included 1


#include "y/cameo/multiplier/api.hpp"
#include "y/cameo/multiplier/synod/fp-list.hpp"

namespace Yttrium
{

    namespace Cameo
    {

        //______________________________________________________________________
        //
        //
        //
        //! Use ordered by exponent values to compute product
        //
        //
        //______________________________________________________________________
        template <typename T>
        class FPointMultiplier : public Multiplier<T>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type);                           //!< aliases
            typedef Synod::FPList<T>              EngineType; //!< alias
            typedef typename EngineType::UnitList UnitList;   //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param n optional capacity
            inline explicit FPointMultiplier(const size_t n=0) : Multiplier<T>(), engine()
            {
                engine.cache(n);
            }

            //! cleanup
            inline virtual ~FPointMultiplier() noexcept {}

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline virtual void ld1() noexcept { engine.free(); }

            inline virtual T product()
            {
                return engine.product();
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            inline Caching *       operator->()       noexcept { return &engine; } //!< \return cache access
            inline const Caching * operator->() const noexcept { return &engine; } //!< \return cache access
            inline const UnitList & operator*() const noexcept { return *engine; } //!< \return internal state



        private:
            Y_Disable_Copy_And_Assign(FPointMultiplier); //!< discarding
            EngineType engine; //!< internal state

            virtual void mul(ParamType x)           { engine.push(x);   }
            virtual void mul(ParamType x, size_t n) { engine.push(x,n); }
        };
    }

}

#endif

