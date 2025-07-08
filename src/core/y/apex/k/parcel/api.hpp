
//! \file

#ifndef Y_Apex_ParcelAPI_Included
#define Y_Apex_ParcelAPI_Included 1

#include "y/apex/k/plan.hpp"
#include "y/apex/metrics.hpp"
#include "y/memory/buffer/rw.hpp"

namespace Yttrium
{
    namespace Apex
    {

        //______________________________________________________________________
        //
        //
        //! helper to perform check
        //
        //______________________________________________________________________
#define Y_Apex_Parcel_Check(EXPR) \
do { if ( !(EXPR) ) { std::cerr << " *** '" << #EXPR << "' failure'" << std::endl; return false; } } while(false)

        //______________________________________________________________________
        //
        //
        //
        //! common API for Parcel<T>
        //
        //
        //______________________________________________________________________
        class ParcelAPI : public Memory::ReadWriteBuffer
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________

            //! human readable aliases
            static const char * const HumanReadablePlan[Metrics::Plans];

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! set capacity in words \param capa capacity
            explicit ParcelAPI(const size_t capa) noexcept :
            Memory::ReadWriteBuffer(),
            size(0),
            maxi(capa)
            {
            }

            //! cleanup
            virtual ~ParcelAPI() noexcept
            {
            }

            //! display \param os output stream \param self *this \return os
            friend std::ostream & operator<<(std::ostream &os, const ParcelAPI &self)
            {
                return self.print(os);
            }

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void   adjust()                     noexcept = 0; //!< adjust size
            virtual void   resize(const size_t numBits) noexcept = 0; //!< set size \param numBits to compute size
            virtual size_t bits()                 const noexcept = 0; //!< \return bit count
            virtual void   naught(ParcelAPI * const[])  noexcept = 0; //!< set to zero
            virtual void   setOne(ParcelAPI * const[])  noexcept = 0; //!< set to one
            virtual size_t shr(ParcelAPI * const[])     noexcept = 0; //!< right shift \return bit count

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            bool   sanity()                   const noexcept; //!< \return true iff sane

            //! update
            /**
             adjust, count bits, syncrhonize and return bits
             \param sync other to resize
             \return numBits
             */
            size_t update(ParcelAPI * const sync[]) noexcept;




            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            size_t       size; //!< size in words
            const size_t maxi; //!< capacity in words

        private:
            Y_Disable_Copy_And_Assign(ParcelAPI); //!< discarding
            virtual bool           check()        const noexcept = 0; //!< \return true iff sane
            virtual std::ostream & print(std::ostream &)   const = 0; //!< \return displayed as hex

        public:

            //! propagate bits to parcel to synchronize
            /**
             \param sync     other parcels to resize
             \param numBits current bits
             \return numBits
             */
            static size_t Propagate(ParcelAPI * const sync[], const size_t numBits) noexcept
            {
                assert(0!=sync[0]); sync[0]->resize(numBits);
                assert(0!=sync[1]); sync[1]->resize(numBits);
                assert(0!=sync[2]); sync[2]->resize(numBits);
                return numBits;
            }

        };

    }

}

#endif

