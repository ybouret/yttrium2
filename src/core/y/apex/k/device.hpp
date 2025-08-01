
//! \file

#ifndef Y_Apex_Device_Included
#define Y_Apex_Device_Included 1

#include "y/apex/k/parcels.hpp"

#include "y/object.hpp"
#include "y/stream/output.hpp"
#include "y/stream/input.hpp"
#include "y/string.hpp"
#include "y/apex/k/ops.hpp"
#include "y/type/copy-of.hpp"

namespace Yttrium
{
    namespace Apex
    {
        //______________________________________________________________________
        //
        //
        //
        //! Implement operations on Parcels
        //
        //
        //______________________________________________________________________
        class Device : public Object, public Parcels
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const size_t   NumOps = Ops32_64+1; //!< inner schems
            static const PlanType SmallPlan[NumOps];   //!< small plan for inner scheme
            static uint64_t *     ProbeMUL;            //!< internal timings if not NULL

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! prepare device
            /**
             \param userBlockSize minimal bytes
             \param userBlockPlan initial plan
             */
            explicit Device(const size_t   userBlockSize,
                            const PlanType userBlockPlan);

            //! format device for integral type
            explicit Device(const CopyOf_ &,const uint64_t);

            //! duplicate device
            Device(const Device &);




            //! cleanup
            virtual ~Device() noexcept;

            //__________________________________________________________________
            //
            //
            // Reload
            //
            //__________________________________________________________________

            //! \return previously written device
            static Device * Load(InputStream &, const char * const = 0);

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void   ld(const uint64_t) noexcept; //!< set to integral type
            void   shr()              noexcept; //!< right shift
            String hex()                 const; //!< \return hexadecimal string
            size_t srz(OutputStream &)   const; //!< \return serialized bytes
            void   com()              noexcept; //!< propagate precomputed bits
            void   fix()              noexcept; //!< set bits to api->update()

            //__________________________________________________________________
            //
            //
            // Comparisons
            //
            //__________________________________________________________________

            //! \return comparison
            static SignType Compare(const Device &,
                                    const Device &,
                                    const PlanType) noexcept;

            //! \return comparison
            static SignType Compare(const Device & ,
                                    const natural_t,
                                    const PlanType ) noexcept;

            //! \return comparison
            static SignType Compare(const natural_t,
                                    const Device & ,
                                    const PlanType ) noexcept;

            //__________________________________________________________________
            //
            //
            // Additions
            //
            //__________________________________________________________________
            static Device * Add(const Device &, const Device  &, OpsMode); //!< \return addition
            static Device * Add(const Device &, const natural_t, OpsMode); //!< \return addition


            //__________________________________________________________________
            //
            //
            // Subtractions
            //
            //__________________________________________________________________
            static Device * Sub(const Device  &, const Device  &, OpsMode); //!< \return subtraction
            static Device * Sub(const Device  &, const natural_t, OpsMode); //!< \return subtraction
            static Device * Sub(const natural_t, const Device  &, OpsMode); //!< \return subtraction

            //__________________________________________________________________
            //
            //
            // Multiplications
            //
            //__________________________________________________________________
            static Device * Mul(const Device &, const Device  &, OpsMode); //!< \return multiplication
            static Device * Mul(const Device &, const natural_t, OpsMode); //!< \return multiplication
            static Device * MulDFT(const Device &, const Device &);        //!< \return mutliplication with DFT
            static Device * MulDFT(const Device &, const natural_t);       //!< \return multiplication with DFT

            //__________________________________________________________________
            //
            //
            // Square
            //
            //__________________________________________________________________
            static Device * Sqr(const Device &, OpsMode); //!< \return square
            static Device * SqrDFT(const Device &);       //!< \return square with DFT

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t   bits;  //!< current bits
            const size_t & bytes; //!< current bytes in Plan8
            const size_t & space; //!< in bytes
            
        private:
            Y_Disable_Assign(Device); //!< discarding
            
        };


    }

}

#endif
