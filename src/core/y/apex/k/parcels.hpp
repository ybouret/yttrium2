
//! \file

#ifndef Y_Apex_Parcels_Included
#define Y_Apex_Parcels_Included 1

#include "y/apex/k/parcel.hpp"

namespace Yttrium
{
    namespace Apex
    {

        enum ExchangePolicy
        {
            ExchangeBuiltInEndian,
            ExchangeNeutralEndian
        };

        class Parcels
        {
        public:


            typedef Parcel<uint8_t> ParcelProto;
            static const unsigned   ParcelProtoSize = sizeof(ParcelProto);
            static const unsigned   ParcelProtoBytes = Metrics::Views * ParcelProtoSize;
            static const size_t     ParcelProtoWords = Alignment::WordsGEQ<ParcelProtoBytes>::Count;

            typedef void            (Parcels:: *Exch)(const PlanType) const;

            static ExchangePolicy  GetExchangePolicy() noexcept;
            static void            SetExchangePolicy(const ExchangePolicy) noexcept;




            explicit Parcels(const size_t   userBlockSize,
                             const PlanType userBlockPlan);
            explicit Parcels(const Parcels &other);
            virtual ~Parcels() noexcept;
            Y_OSTREAM_PROTO(Parcels);

            template <typename T> inline
            Parcel<T> & get() noexcept
            {
                assert( IntegerLog2For<T>::Value == plan );
                return parcel<T>();
            }

            template <typename T> inline
            const Parcel<T> & get() const noexcept
            {
                assert( IntegerLog2For<T>::Value == plan );
                return parcel<T>();
            }

            template <typename T> inline
            Parcel<T> & make() noexcept
            {
                set( PlanType(  IntegerLog2For<T>::Value ) );
                return parcel<T>();
            }

            void set(const PlanType userPlan) const noexcept;
            void ldz(const PlanType userPlan) noexcept;
            void ld1(const PlanType userPlan) noexcept;

            size_t update() noexcept
            {
                return api->update( sync[plan] );
            }

            void    exchLE(const PlanType) const noexcept; //!< Little Endian code
            void    exchEN(const PlanType) const noexcept; //!< Endian Neutral code
            
        private:
            Y_Disable_Assign(Parcels);
            uint8_t * const   addr;
        public:
            const PlanType    plan;
            ParcelAPI * const api;

        private:
            Exch              exch;
            ParcelAPI * const sync[Metrics::Views][Metrics::Views-1];
            void    *         wksp[ParcelProtoWords];
            unsigned          blockShift;
            const size_t      blockBytes;
            void * const      blockEntry;

            void   selectAPI()       noexcept;
            void   initialize()      noexcept;

            static uint8_t * Query(const unsigned shift);

        protected:
            //! \return parcel by type
            template <typename T>
            inline Parcel<T> & parcel() const noexcept {
                return *(Parcel<T> *) &addr[ParcelProtoSize*IntegerLog2For<T>::Value];
            }
        };

    }

}


#endif

