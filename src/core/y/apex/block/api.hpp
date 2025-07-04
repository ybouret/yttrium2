

//! \file

#ifndef Y_Apex_Block_API_Included
#define Y_Apex_Block_API_Included 1

#include "y/apex/metrics.hpp"
#include "y/apex/block/view.hpp"

namespace Yttrium
{
    namespace Apex
    {
        

        //! helper to build debug functions
#define Y_Block_Check(EXPR) do { \
if ( !(EXPR) ) { std::cerr << #EXPR << " failure" << std::endl; return false; } \
} while(false)


        //______________________________________________________________________
        //
        //
        //
        //! Base class for concrete Block(s)
        //
        //
        //______________________________________________________________________
        class BlockAPI
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const ViewType VTable[Metrics::Views]; //!< integer to view table

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            //! initialize
            /**
             \param n maxi
             \param v view
             */
            explicit BlockAPI(const size_t   n,
                              const ViewType v);

        public:
            virtual ~BlockAPI() noexcept; //!< cleanup
            Y_OSTREAM_PROTO(BlockAPI);    //!< display by print()

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual size_t   update(BlockAPI * const [])  noexcept = 0;   //!< update, sync  \return bits
            virtual void     naught(BlockAPI * const [])  noexcept = 0;   //!< set to zero with sync
            virtual void     build1(BlockAPI * const [])  noexcept = 0;   //!< set to one   with sync
            virtual void     resize(const size_t numBits) noexcept = 0;   //!< set size \param numBits computed bits
            virtual uint64_t little()               const noexcept = 0;   //!< \return little 64 bits
            virtual size_t   shr(BlockAPI * const [])     noexcept = 0;   //!< in-place shift right \return numBits
            bool             isValid()              const noexcept;       //!< full check, mostly for debug \return validity
            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            size_t                size; //!< current size <= maxi
            const size_t          maxi; //!< capacity
            const ViewType        view; //!< assigned view

        private:
            Y_Disable_Copy_And_Assign(BlockAPI); //!< discarding
            virtual bool           doCheck()   const noexcept = 0; //!< full check \return validity
            virtual std::ostream & print(std::ostream&) const = 0; //!< display \return output stream

        };


    }

}

#endif
