//! \file
//!
#ifndef Y_Coven_Survey_Included
#define Y_Coven_Survey_Included 1

#include "y/apex/api/coven/types.hpp"
#include "y/stream/xmlog.hpp"

namespace Yttrium
{

    namespace Coven
    {

        //______________________________________________________________________
        //
        //
        //
        //! Survey of vectors, ordered
        //
        //
        //______________________________________________________________________
        class Survey : public Ingress< const Core::ListOf<QVector> >
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup with vector pool for memory
            explicit Survey(QVector::Pool &) noexcept;

            //! cleanup
            virtual ~Survey() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void reset() noexcept;         //!< vector in pool, calls=0;
            void collect(XMLog &,const QVector &); //!< collect vector, no duplicate

            //! test equality, mostly to debug
            friend bool operator==(const Survey &, const Survey &) noexcept;

        private:
            Y_Disable_Copy_And_Assign(Survey); //!< discarding
            virtual ConstInterface & locus() const noexcept;

            QVector::List   list; //!< current list
            QVector::Pool & pool; //!< pool for memory
            
        public:
            const size_t    calls; //!< current calls
        };
    }

}

#endif

