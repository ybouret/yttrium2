//! \file

#ifndef Y_MKL_Statistics_Average_Included
#define Y_MKL_Statistics_Average_Included 1

#include "y/cameo/addition.hpp"
#include "y/mkl/api/fcpu.hpp"
#include "y/static/moniker.hpp"

namespace Yttrium
{
    namespace MKL
    {

        namespace Statistics
        {
            //__________________________________________________________________
            //
            //
            //
            //! flexible average computation
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Average  : public Container, public Recyclable
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef typename FCPU<T>::Type fcpu_t; //!< alias
                Y_Args_Declare(T,Type);                //!< aliases

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                inline explicit Average() :
                Container(),
                Recyclable(),
                xadd(),
                nadd(0),
                zero()
                {}

                //! cleanup
                inline virtual ~Average() noexcept {}

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                inline virtual size_t size() const noexcept { return nadd; }
                inline virtual void   free() noexcept { xadd.ldz(); nadd = 0; }

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! append data \param args value \return *this
                inline Average & operator<<(ParamType args)
                {
                    xadd << args;
                    ++nadd;
                    return *this;
                }

                //! compute average from current state \return averaged values
                inline T operator()(void)
                {
                    try {
                        if(nadd<=0) return *zero;
                        const fcpu_t denom = (fcpu_t)nadd;
                        ConstType    numer = xadd.sum();
                        return numer/denom;
                    }
                    catch(...)
                    {
                        free();
                        throw;
                    }
                }

                //! \param it iterator \param n items \return range average
                template <typename ITER> inline
                T operator()(ITER it, size_t n)
                {
                    Average &self = *this;
                    free();
                    while(n-- > 0) self << *(it++);
                    return self();
                }

                //! \param seq sequence-like \return sequence average
                template <typename SEQ> inline
                T operator()(const SEQ &seq)
                {
                    return (*this)(seq.begin(),seq.size());
                }




            private:
                Y_Disable_Copy_And_Assign(Average); //!< discarding
                Cameo::Addition<T>       xadd;      //!< inner addition
                size_t                   nadd;      //!< current count
            public:
                const Static::Moniker<T> zero;      //!< zero value

            };

        }

    }
}

#endif // !Y_MKL_Statistics_Average_Included
