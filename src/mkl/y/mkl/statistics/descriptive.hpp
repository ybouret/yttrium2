
//! \file

#ifndef Y_MKL_Statistics_Descriptive_Included
#define Y_MKL_Statistics_Descriptive_Included 1

#include "y/cameo/addition.hpp"
#include "y/mkl/api/fcpu.hpp"
#include "y/static/moniker.hpp"
#include "y/mkl/api/fabs.hpp"
#include "y/mkl/api/sqrt.hpp"


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
            //! Descriptive values
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Descriptive
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
                inline explicit Descriptive() : xadd(), zero(), three(3) {} //!< setup
                inline virtual ~Descriptive() noexcept {}                   //!< cleanup


                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! \param it iterator \param n items \return range average
                template <typename ITER> inline
                T average(ITER it, size_t n)
                {
                    if(n<=0) return *zero;
                    ConstType denom = (fcpu_t)n;
                    xadd.ldz();
                    while(n-- > 0) xadd << *(it++);
                    return xadd.sum()/denom;
                }

                //! \param seq sequence like \return sequence average
                template <typename SEQ> inline
                T average(const SEQ &seq) { return average(seq.begin(),seq.size()); }


                //! \param it iterator \param n items \param ave average \return range variance
                template <typename ITER> inline
                T variance(ITER it, size_t n, ParamType ave)
                {
                    if(n<=1) return *zero;
                    ConstType denom = (fcpu_t)(n-1);
                    xadd.ldz();
                    while(n-- > 0) {
                        ConstType delta = *(it++)-ave;
                        ConstType delsq = delta*delta;
                        xadd << delsq;
                    }
                    return xadd.sum()/denom;
                }
                //! \param seq sequence like \param ave average \return sequence variance
                template <typename SEQ> inline
                T variance(const SEQ &seq, ParamType ave)
                {
                    return variance(seq.begin(),seq.size(),ave);
                }

                //! \param it iterator \param n items \param ave average \return range standard deviation
                template <typename ITER> inline
                T stddev(ITER it, size_t n, ParamType ave)
                {
                    const T var = variance(it,n,ave);
                    return Sqrt<T>::Of(var);
                }

                //! \param seq sequence like \param ave average \return sequence standard deviation
                template <typename SEQ> inline
                T stddev(const SEQ &seq, ParamType ave)
                {
                    const T var = variance(seq,ave);
                    return Sqrt<T>::Of(var);
                }

                //! \param it iterator \param n items \param ave average \return range absolute deviation
                template <typename ITER> inline
                T absdev(ITER it, size_t n, ParamType ave)
                {
                    if(n<=1) return *zero;
                    ConstType denom = (fcpu_t)n;
                    xadd.ldz();
                    while(n-- > 0) {
                        ConstType delta = *(it++)-ave;
                        ConstType del_a = Fabs<T>::Of(delta);
                        xadd << del_a;
                    }
                    return xadd.sum()/denom;
                }

                //! \param seq sequence like \param ave average \return sequence absolute deviation
                template <typename SEQ> inline
                T absdev(const SEQ &seq, ParamType ave)
                {
                    return absdev(seq.begin(),seq.size(),ave);
                }

                //! \param it iterator \param n items \param ave average \param sig standard deviation \return range skenwess
                template <typename ITER> inline
                T skewness(ITER it, size_t n, ParamType ave, ParamType sig)
                {
                    if(n<=1) return *zero;
                    ConstType denom = (fcpu_t)n;
                    xadd.ldz();
                    while(n-- > 0)
                    {
                        ConstType arg = (*(it++)-ave)/sig;
                        ConstType arg3 = arg*arg*arg;
                        xadd << arg3;
                    }
                    return xadd.sum()/denom;
                }
                //! \param seq sequence like \param ave average \param sig standard deviation \return sequence skenwess
                template <typename SEQ> inline
                T skewness(const SEQ &seq, ParamType ave, ParamType sig)
                {
                    return skewness(seq.begin(),seq.size(),ave,sig);
                }

                //! \param it iterator \param n items \param ave average \param sig standard deviation \return range kurtosis
                template <typename ITER> inline
                T kurtosis(ITER it, size_t n, ParamType ave, ParamType sig)
                {
                    if(n<=1) return *zero;
                    ConstType denom = (fcpu_t)n;
                    xadd.ldz();
                    while(n-- > 0)
                    {
                        ConstType arg  = (*(it++)-ave)/sig;
                        ConstType arg2 = arg*arg;
                        ConstType arg4 = arg2*arg2;
                        xadd << arg4;
                    }
                    return xadd.sum()/denom - *three;
                }

                //! \param seq sequence like \param ave average \param sig standard deviation \return sequence kurtosis
                template <typename SEQ> inline
                T kurtosis(const SEQ &seq, ParamType ave, ParamType sig)
                {
                    return kurtosis(seq.begin(),seq.size(),ave,sig);
                }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                Cameo::Addition<T>               xadd;  //!< inner additions
                const Static::Moniker<ConstType> zero;  //!< zero
                const Static::Moniker<ConstType> three; //!< three

            private:
                Y_Disable_Copy_And_Assign(Descriptive); //!< discarding
            };
        }

    }

}

#endif // !Y_MKL_Statistics_Descriptive_Included
