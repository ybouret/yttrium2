
//! \file

#ifndef Y_MKL_Tao_BrokerBasis_Included
#define Y_MKL_Tao_BrokerBasis_Included 1

#include "y/cameo/caddy.hpp"

namespace Yttrium
{

    namespace MKL
    {

        namespace Tao
        {
            //__________________________________________________________________
            //
            //
            //
            //! basis class for brokers: hold Cameo::Caddy
            //
            //
            //__________________________________________________________________
            template <typename T>
            class BrokerBasis
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Cameo::Addition<T> XAddition; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param numThreads threads count
                inline explicit BrokerBasis(const size_t numThreads) :
                caddy()
                {
                    (void) caddy.adjust( numThreads <= 0 ? 1 : numThreads );
                }

                //! cleanup
                inline virtual ~BrokerBasis() noexcept {}


                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! \return first, always present XAddition
                inline XAddition & xadd() noexcept {
                    assert(caddy.head);
                    return *caddy.head;
                }

            protected:
                Cameo::Caddy<T>  caddy;  //!< xadditions

            private:
                Y_Disable_Copy_And_Assign(BrokerBasis); //!< discarding
            };
        }

    }

}

#endif // !Y_MKL_Tao_BrokerBasis_Included
