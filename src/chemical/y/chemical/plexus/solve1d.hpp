//! \file


#ifndef Y_Chemical_Solve1D_Included
#define Y_Chemical_Solve1D_Included 1


#include "y/chemical/reactive/components.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! Solve one equilibrium
        //
        //
        //______________________________________________________________________
        class Solve1D
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Solve1D"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Solve1D();          //!< setup
            virtual ~Solve1D() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! solve and compute average extent
            /**
             \param E  components
             \param K  constant for components
             \param C  concentrations, initially C0
             \param L  level
             \param C0 original concentrations
             \return average extent
             */
            xreal_t operator()(const Components &E,
                               const xreal_t     K,
                               XWritable        &C,
                               const Level       L,
                               const XReadable  &C0);

        private:
            class Code;
            Y_Disable_Copy_And_Assign(Solve1D); //!< disarding
            Code * const code; //!< inner code
        public:
            XMul &       xmul; //!< inner xmul, to be reused
        };
    }

}

#endif

