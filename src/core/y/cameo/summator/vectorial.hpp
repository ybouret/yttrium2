
//! \file

#ifndef Y_Cameo_VectorialSummator_Included
#define Y_Cameo_VectorialSummator_Included 1

#include "y/cameo/summator/scalar.hpp"
#include "y/cameo/genus/vectorial.hpp"
#include "y/memory/operating.hpp"

namespace Yttrium
{

    namespace Cameo
    {


        //______________________________________________________________________
        //
        //
        //
        //! multiple scalar summators
        //
        //
        //______________________________________________________________________
        template <typename T>
        class VectorialSummator : public Summator<T>, public VectorialGenus
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type);                                 //!< aliases
            typedef typename MKL::ScalarFor<T>::Type ScalarType;    //!< alias
            typedef ScalarSummator<ScalarType>       CoordSummator; //!< alias
            static const size_t DIMENSIONS = MutableType::DIMENSIONS; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! default
            inline explicit VectorialSummator() :
            Summator<T>(),
            VectorialGenus(CoordSummator::CallSign),
            summators(DIMENSIONS),
            operating(summators.entry,DIMENSIONS)
            {}

            //! for FPointSummators \param n minimal capacity
            inline explicit VectorialSummator(const size_t n) :
            Summator<T>(),
            VectorialGenus(CoordSummator::CallSign),
            summators(DIMENSIONS),
            operating(CopyOf,n,summators.entry,DIMENSIONS)
            {}

            //! cleanup
            inline virtual ~VectorialSummator() noexcept
            {
            }


            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline virtual const char * callSign() const noexcept { return identifier; }
            
            inline virtual void ldz() noexcept
            {
                for(size_t i=0;i<DIMENSIONS;++i) summators.entry[i].ldz();
            }

            inline virtual T sum() {
                try
                {
                    T res;
                    {
                        ScalarType * const coord = Memory::Stealth::Cast<ScalarType>( &res );
                        for(size_t i=0;i<DIMENSIONS;++i)
                            coord[i] = summators.entry[i].sum();
                    }
                    ldz();
                    return res;
                }
                catch(...)
                {
                    ldz();
                    throw;
                }
            }


        private:
            Y_Disable_Copy_And_Assign(VectorialSummator); //!< discarding
            Memory::SchoolOf<CoordSummator>   summators;  //!< workspace for summators
            Memory::Operating<CoordSummator>  operating;  //!< I/O for summators
            
            inline virtual void add(ParamType value)
            {
                try {
                    const ScalarType * const coord = Memory::Stealth::Cast<ScalarType>( &value );
                    for(size_t i=0;i<DIMENSIONS;++i)
                        summators.entry[i] << coord[i];
                }
                catch(...)
                {
                    ldz();
                    throw;
                }
            }
        };
    }

}

#endif

