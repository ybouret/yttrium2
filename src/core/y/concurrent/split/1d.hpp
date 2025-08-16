
//! \file


#ifndef Y_Concurrent_Split1D_Included
#define Y_Concurrent_Split1D_Included 1

#include "y/concurrent/member.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Split
        {

            //__________________________________________________________________
            //
            //
            //
            //! offset+length
            //
            //
            //__________________________________________________________________
            class Zone
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                Zone()            noexcept; //!< setup to zeor
                Zone(const Zone&) noexcept; //!< duplicate
                virtual ~Zone()   noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const size_t offset; //!< cumulative offset
                const size_t length; //!< dedicated  length from offset
            private:
                Y_Disable_Assign(Zone); //!< discarding
            };

            //__________________________________________________________________
            //
            //
            //
            //! Stable burden division
            //
            //
            //__________________________________________________________________
            class In1D : public Zone
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                In1D(const size_t) noexcept; //!< setup with burden
                virtual ~In1D()    noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! initialize
                /**
                 \param numProcessors target count of cpu
                 \param initialOffset to propagate
                 */
                void boot(const size_t numProcessors,
                          const size_t initialOffset) noexcept;

                //! \return true if a new zone was computer
                bool next() noexcept;

                //! \return matching zone with initial offset
                Zone operator()(const Member &, const size_t) noexcept;

            private:
                size_t       divide; //!< internal divide
                size_t       remain; //!< internal remain
            public:
                const size_t burden; //!< original burden
            private:
                Y_Disable_Copy_And_Assign(In1D); //!< discarding
            };

        }

    }
}

#endif

