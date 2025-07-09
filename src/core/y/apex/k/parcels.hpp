
//! \file

#ifndef Y_Apex_Parcels_Included
#define Y_Apex_Parcels_Included 1

#include "y/apex/k/parcel.hpp"

namespace Yttrium
{
    namespace Apex
    {


        //! how to exchange views
        enum TransmutePolicy
        {
            TransmuteBuiltInEndian, //!< using Endian::Little/Big
            TransmuteNeutralEndian  //!< force using Transmute::To
        };

        //______________________________________________________________________
        //
        //
        //
        //! Parcels of different Plan, same data
        //
        //
        //______________________________________________________________________
        class Parcels
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Parcel<uint8_t> ParcelProto;                                                     //!< alias
            static const unsigned   ParcelProtoSize = sizeof(ParcelProto);                           //!< aloas
            static const unsigned   ParcelProtoBytes = Metrics::Plans * ParcelProtoSize;             //!< alias
            static const size_t     ParcelProtoWords = Alignment::WordsGEQ<ParcelProtoBytes>::Count; //!< alias

            typedef void            (Parcels:: *Exch)(const PlanType) const;         //!< method pointer
            static TransmutePolicy  GetTransmutePolicy()                     noexcept; //!< \return current global policy
            static void             SetTransmutePolicy(const TransmutePolicy) noexcept; //!< set current global policy



            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________


            //! setup
            /**
             \param userBlockSize total bytes
             \param userBlockPlan initial plan
             */
            explicit Parcels(const size_t   userBlockSize,
                             const PlanType userBlockPlan);

            //! duplicate
            explicit Parcels(const Parcels &);

            //! cleanup
            virtual ~Parcels() noexcept;

            //! display
            Y_OSTREAM_PROTO(Parcels);

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return current plan
            template <typename T> inline Parcel<T> & get() noexcept
            {
                assert( IntegerLog2For<T>::Value == plan );
                return parcel<T>();
            }

            //! \return const current plan
            template <typename T> inline
            const Parcel<T> & get() const noexcept
            {
                assert( IntegerLog2For<T>::Value == plan );
                return parcel<T>();
            }

            //! \return current view, transmuted
            template <typename T> inline Parcel<T> & make() noexcept
            {
                set( PlanType(  IntegerLog2For<T>::Value ) );
                return parcel<T>();
            }

            //! \return const current view, transmuted
            template <typename T> inline const Parcel<T> & make() const noexcept
            {
                set( PlanType(  IntegerLog2For<T>::Value ) );
                return parcel<T>();
            }

            void   set(const PlanType) const noexcept; //!< transmute
            void   ldz(size_t &, const PlanType) noexcept;       //!< load zero, zero bits, transmute
            void   ld1(size_t &, const PlanType) noexcept;       //!< load one, one bitstransmuste

            void    exchLE(const PlanType) const noexcept; //!< Little Endian code
            void    exchEN(const PlanType) const noexcept; //!< Endian Neutral code

            size_t  synchronize() noexcept; //!< \return api->update( sync[plan] )

        private:
            Y_Disable_Assign(Parcels); //!< discarding
            uint8_t * const   addr;    //!< from wksp
        public:
            const PlanType    plan;    //!< current plan
            ParcelAPI * const api;     //!< current api
        private:
            Exch              exch;    //!< exchange method
        public:
            ParcelAPI * const sync[Metrics::Plans][Metrics::Plans-1]; //!< synchronized peers
        private:
            void    *         wksp[ParcelProtoWords]; //!< to store parcless
            unsigned          blockShift;             //!< for memory
            const size_t      blockBytes;             //!< for memory
            void * const      blockEntry;             //!< memory

            void             selectAPI()  noexcept; //!< from plan
            void             initialize() noexcept; //!< full setup
            static uint8_t * Query(const unsigned); //!< \return from archon

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

