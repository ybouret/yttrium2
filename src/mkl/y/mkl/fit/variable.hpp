

//! \file

#ifndef Y_Fit_Variable_Included
#define Y_Fit_Variable_Included 1

#include "y/mkl/fit/entity.hpp"
#include "y/pointer/keyed.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            class Variable : public Entity
            {
            public:
                typedef Keyed< String, ArcPtr<Variable> > Pointer;

            protected:
                template <typename UID> inline
                explicit Variable(const UID  & uid,
                                  const size_t primaryIndex,
                                  const size_t workingIndex) :
                Entity(uid), primary(primaryIndex), working(workingIndex)
                {
                }

            public:
                virtual ~Variable() noexcept;

                friend std::ostream & operator<<(std::ostream &, const Variable &);

                const size_t primary;
                const size_t working;
            private:
                Y_Disable_Copy_And_Assign(Variable);
                virtual std::ostream & display(std::ostream &) const = 0;
            };

            class PrimaryVariable : public Variable
            {
            public:
                template <typename UID> inline
                explicit PrimaryVariable(const UID &uid, const size_t idx) :
                Variable(uid,idx,idx)
                {
                }

                virtual ~PrimaryVariable() noexcept;


            private:
                Y_Disable_Copy_And_Assign(PrimaryVariable);
                virtual std::ostream & display(std::ostream &) const;
            };

            class ReplicaVariable : public Variable
            {
            public:
                template <typename UID> inline
                explicit ReplicaVariable(const UID &             uid,
                                         const PrimaryVariable & var,
                                         const size_t             primaryIndex) :
                Variable(uid,primaryIndex,var.primary),
                alias(var)
                {
                }

                virtual ~ReplicaVariable() noexcept;

            private:
                Y_Disable_Copy_And_Assign(ReplicaVariable);
                const PrimaryVariable & alias;

                virtual std::ostream & display(std::ostream &) const;
            };

        }

    }

}

#endif // !Y_Fit_Variable_Included

