
//! \file

#ifndef Y_Apex_ParcelAPI_Included
#define Y_Apex_ParcelAPI_Included 1

#include "y/apex/k/plan.hpp"
#include "y/apex/metrics.hpp"

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Apex
    {

        
#define Y_Apex_Parcel_Check(EXPR) \
do { if ( !(EXPR) ) { std::cerr << " *** '" << #EXPR << "' failure'" << std::endl; return false; } } while(false)

        class ParcelAPI
        {
        public:
            static const char * const HumanReadablePlan[Metrics::Views];

            explicit ParcelAPI(const size_t capa) noexcept :
            size(0),
            maxi(capa)
            {
            }

            virtual ~ParcelAPI() noexcept
            {
            }

            friend std::ostream & operator<<(std::ostream &os, const ParcelAPI &self)
            {
                return self.print(os);
            }

            bool sanity() const noexcept;

            virtual void   adjust()                     noexcept = 0;
            virtual void   resize(const size_t numBits) noexcept = 0;
            virtual size_t bits()                 const noexcept = 0;
            virtual void   naught(ParcelAPI * const[])  noexcept = 0;
            size_t         update(ParcelAPI * const sync[]) noexcept
            {
                assert(sync);
                adjust(); assert( sanity() );
                const size_t numBits  = bits();
                assert(0!=sync[0]); sync[0]->resize(numBits);
                assert(0!=sync[1]); sync[1]->resize(numBits);
                assert(0!=sync[2]); sync[2]->resize(numBits);
                return numBits;
            }

            size_t       size; //!< size in words
            const size_t maxi; //!< capacity in words

        private:
            Y_Disable_Copy_And_Assign(ParcelAPI);
            virtual bool           check() const noexcept = 0;
            virtual std::ostream & print(std::ostream &os) const = 0;
        };

    }

}

#endif

