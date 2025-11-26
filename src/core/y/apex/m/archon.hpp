
//! \file

#ifndef Y_Apex_Archon_Included
#define Y_Apex_Archon_Included 1

#include "y/apex/metrics.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/apex/m/jmutex.hpp"
#include "y/core/linked/list/cxx.hpp"

namespace Yttrium
{
    namespace Memory { class Quanta; }

    namespace Apex
    {

        //______________________________________________________________________
        //
        //
        //
        //! Cache from Memory::Quanta for blocks I/O
        //
        //
        //______________________________________________________________________
        class Archon : public Singleton<Archon,ClassLockPolicy>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const          CallSign;                                              //!< "Apex::Archon"
            static const Longevity             LifeTime  = LifeTimeOf::ApexMemory;                    //!< lifetime
            static const unsigned              MinShift  = Metrics::MinShift;                         //!< 2^MinShift bytes
            static const unsigned              MaxShift  = Metrics::MaxShift;                         //!< 2^MaxShift byte
            static const unsigned              NumShifts = Metrics::MaxShift - Metrics::MinShift + 1; //!< possibilities
            class Slot;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void display(std::ostream &,size_t) const;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void *       query(const unsigned shift);                              //!< \param shift valid shift \return 2^shift bytes
            void         store(const unsigned shift, void * const block) noexcept; //!< store \param shift 2^shift bytes \param block queried

            JointMutex      *queryMutex();                            //!< \return usable mutex
            void             storeMutex(JointMutex * const) noexcept; //!< store used mutex


        private:
            friend class Singleton<Archon, ClassLockPolicy>;
            Y_Disable_Copy_And_Assign(Archon); //!< discarding

            explicit Archon();           //!< setup
            virtual ~Archon() noexcept;  //!< cleanup

            Slot * const          slots;      //!< caches
            Memory::Quanta  &     quanta;     //!< lower level memory
            CxxListOf<JointMutex> jlist;      //!< joint mutexes
        };

       
    }

}

#endif // !Y_Apex_Archon_Included

