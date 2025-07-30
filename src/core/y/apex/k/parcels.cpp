
#include "y/apex/k/parcels.hpp"
#include "y/apex/m/archon.hpp"
#include "y/system/endian.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Apex
    {


        namespace
        {
            static TransmutePolicy _TransmutePolicy = TransmuteBuiltInEndian;

            static Parcels::Exch ChooseTransmuteMethod() noexcept
            {
                switch( _TransmutePolicy )
                {
                    case TransmuteBuiltInEndian:
                        if( Endian::Little() )
                            return & Parcels:: exchLE;
                        else
                            return & Parcels::exchEN;

                    case TransmuteNeutralEndian:
                        return & Parcels:: exchEN;
                }

                return & Parcels:: exchEN;

            }

            static Parcels::Exch _TransmuteMethod = ChooseTransmuteMethod();
        }

        TransmutePolicy  Parcels:: GetTransmutePolicy() noexcept
        {
            return _TransmutePolicy;
        }

        void Parcels:: SetTransmutePolicy(const TransmutePolicy ep) noexcept
        {
            static Lockable &access = Archon::Instance().access;
            Y_Lock(access);
            _TransmutePolicy = ep;
            _TransmuteMethod = ChooseTransmuteMethod();
        }



        Parcels:: Parcels(const size_t   userBlockSize,
                          const PlanType userBlockPlan) :
        addr(0),
        plan(userBlockPlan),
        api(0),
        exch(_TransmuteMethod),
        sync(),
        wksp(),
        blockShift(0),
        blockBytes(Metrics::BytesFor(userBlockSize,blockShift)),
        blockEntry( Query(blockShift) )
        {
            initialize();
        }


        Parcels:: Parcels(const Parcels &other) :
        addr(0),
        plan(other.plan),
        api(0),
        exch(_TransmuteMethod),
        sync(),
        wksp(),
        blockShift(0),
        blockBytes(Metrics::BytesFor(other.parcel<uint64_t>().length(),blockShift)),
        blockEntry( Query(blockShift) )
        {
            initialize();
            parcel<uint8_t>() .size = other.parcel<uint8_t>() .size;
            parcel<uint16_t>().size = other.parcel<uint16_t>().size;
            parcel<uint32_t>().size = other.parcel<uint32_t>().size;
            Parcel<uint64_t> &       target = parcel<uint64_t>();
            const Parcel<uint64_t> & source = other.parcel<uint64_t>();
            memcpy(target.data,source.data,(target.size=source.size) * sizeof(uint64_t) );
        }


        Parcels:: ~Parcels() noexcept
        {
            static Archon & archon = Archon::Location();
            archon.store(blockShift,blockEntry);
        }

        std::ostream & operator<<(std::ostream &os, const Parcels &self)
        {
            return os << *self.api;
        }

        uint8_t * Parcels:: Query(const unsigned shift)
        {
            static Archon & archon = Archon::Instance();
            return static_cast<uint8_t *>( archon.query(shift) );
        }


        void Parcels:: selectAPI() noexcept
        {
            switch(plan)
            {
                case Plan8:  Coerce(api) = & parcel<uint8_t>();  break;
                case Plan16: Coerce(api) = & parcel<uint16_t>(); break;
                case Plan32: Coerce(api) = & parcel<uint32_t>(); break;
                case Plan64: Coerce(api) = & parcel<uint64_t>(); break;
            }
        }

        void Parcels:: initialize() noexcept
        {
            uint8_t * const p = ( Coerce(addr) = static_cast<uint8_t *>( Y_Memory_BZero(wksp) ) );
            new (p)                     Parcel<uint8_t>(blockEntry,blockBytes);
            new (p +   ParcelProtoSize) Parcel<uint16_t>(blockEntry,blockBytes);
            new (p + 2*ParcelProtoSize) Parcel<uint32_t>(blockEntry,blockBytes);
            new (p + 3*ParcelProtoSize) Parcel<uint64_t>(blockEntry,blockBytes);

            Coerce( sync[Plan8][0] ) = & parcel<uint16_t>();
            Coerce( sync[Plan8][1] ) = & parcel<uint32_t>();
            Coerce( sync[Plan8][2] ) = & parcel<uint64_t>();

            Coerce( sync[Plan16][0] ) = & parcel<uint8_t>();
            Coerce( sync[Plan16][1] ) = & parcel<uint32_t>();
            Coerce( sync[Plan16][2] ) = & parcel<uint64_t>();

            Coerce( sync[Plan32][0] ) = & parcel<uint8_t>();
            Coerce( sync[Plan32][1] ) = & parcel<uint16_t>();
            Coerce( sync[Plan32][2] ) = & parcel<uint64_t>();

            Coerce( sync[Plan64][0] ) = & parcel<uint8_t>();
            Coerce( sync[Plan64][1] ) = & parcel<uint16_t>();
            Coerce( sync[Plan64][2] ) = & parcel<uint32_t>();

            selectAPI();
        }


        void Parcels:: ldz(size_t &bits, const PlanType userPlan) noexcept
        {
            api->naught(sync[plan]);
            Coerce(plan) = userPlan;
            bits         = 0;
            selectAPI();
        }

        void Parcels:: ld1(size_t &bits, const PlanType userPlan) noexcept
        {
            api->setOne(sync[plan]);
            Coerce(plan) = userPlan;
            bits         = 1;
            selectAPI();
        }

        void Parcels:: set(const PlanType userPlan) const noexcept
        {
            assert(0!=api);
            assert(api->sanity());
            assert(exch);
            (*this.*exch)(userPlan);
            Coerce(plan) = userPlan;
            Coerce(*this).selectAPI();
        }


        void Parcels:: exchLE(const PlanType) const noexcept
        {
            // do nothing
        }
        
        size_t Parcels::  synchronize() noexcept
        {
            return api->update( sync[plan] );
        }
    }
}

#include "y/apex/k/parcel/transmute.hpp"
namespace Yttrium
{

    namespace Apex
    {

        void Parcels:: exchEN(const PlanType userPlan) const noexcept
        {
            
            switch(plan)
            {
                case Plan8:
                    switch(userPlan)
                    {
                        case Plan8:  Transmute::To(parcel<uint8_t>(), parcel<uint8_t>()); break;
                        case Plan16: Transmute::To(parcel<uint16_t>(),parcel<uint8_t>()); break;
                        case Plan32: Transmute::To(parcel<uint16_t>(),parcel<uint8_t>()); break;
                        case Plan64: Transmute::To(parcel<uint16_t>(),parcel<uint8_t>()); break;
                    }
                    break;

                case Plan16:
                    switch(userPlan)
                    {
                        case Plan8:  Transmute::To(parcel<uint8_t>(), parcel<uint16_t>()); break;
                        case Plan16: Transmute::To(parcel<uint16_t>(),parcel<uint16_t>()); break;
                        case Plan32: Transmute::To(parcel<uint16_t>(),parcel<uint16_t>()); break;
                        case Plan64: Transmute::To(parcel<uint16_t>(),parcel<uint16_t>()); break;
                    }
                    break;

                case Plan32:
                    switch(userPlan)
                    {
                        case Plan8:  Transmute::To(parcel<uint8_t>(), parcel<uint32_t>()); break;
                        case Plan16: Transmute::To(parcel<uint16_t>(),parcel<uint32_t>()); break;
                        case Plan32: Transmute::To(parcel<uint16_t>(),parcel<uint32_t>()); break;
                        case Plan64: Transmute::To(parcel<uint16_t>(),parcel<uint32_t>()); break;
                    }
                    break;

                case Plan64:
                    switch(userPlan)
                    {
                        case Plan8:  Transmute::To(parcel<uint8_t>(), parcel<uint64_t>()); break;
                        case Plan16: Transmute::To(parcel<uint16_t>(),parcel<uint64_t>()); break;
                        case Plan32: Transmute::To(parcel<uint16_t>(),parcel<uint64_t>()); break;
                        case Plan64: Transmute::To(parcel<uint16_t>(),parcel<uint64_t>()); break;
                    }
                    break;
            }
        }



    }

}


