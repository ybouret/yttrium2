//! \file

#ifndef Y_Cameo_DirectSummator_Included
#define Y_Cameo_DirectSummator_Included 1


#include "y/cameo/summator/api.hpp"
#include "y/cameo/genus/direct.hpp"
#include "y/apex/rational.hpp"

namespace Yttrium
{

    namespace Cameo
    {



        //______________________________________________________________________
        //
        //
        //
        //! Direct sum for ap[n|z|q]
        //
        //
        //______________________________________________________________________
        template <typename T>
        class DirectSummator : public Summator<T>, public DirectGenus
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type); //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            inline explicit DirectSummator() : Summator<T>(), acc()
            {
                Y_STATIC_CHECK(Y_Is_SuperSubClass_Strict(Apex::Number,MutableType),NoApexNumber);
            }

            //! cleanup
            inline virtual ~DirectSummator() noexcept {}

            //! display inner state
            inline friend std::ostream & operator<<(std::ostream &os, const DirectSummator &self)
            {
                return os << self.acc;
            }

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline virtual const char * callSign() const noexcept { return CallSign; }

            inline virtual void ldz() noexcept { acc.ldz(); }
            inline virtual T    sum() noexcept
            {
                ConstType res = acc;
                acc.ldz();
                return res;
            }

        private:
            Y_Disable_Copy_And_Assign(DirectSummator); //!< discarding
            MutableType acc; //!< accumulator

        protected:
            inline virtual void add(ParamType x) { acc += x; }
        };
    }
}

#endif // !Y_Cameo_DirectSummator_Included


