
//! \file

#ifndef Y_DFT_Included
#define Y_DFT_Included 1

#include "y/mkl/complex.hpp"
#include "y/calculus/base2.hpp"
#include "y/memory/stealth.hpp"
#include "y/dft/fmt/_4.hpp"
#include "y/dft/fmt/_8.hpp"
#include "y/dft/fmt/_16.hpp"
#include "y/dft/fmt/_32.hpp"
#include "y/dft/fmt/_64.hpp"
#include "y/dft/fmt/_128.hpp"
#include "y/dft/fmt/_256.hpp"
#include "y/dft/fmt/_512.hpp"
#include "y/dft/fmt/_1024.hpp"
#include "y/dft/fmt/_2048.hpp"
#include "y/dft/fmt/_4096.hpp"
#include "y/dft/fmt/_8192.hpp"
#include "y/dft/fmt/_16384.hpp"
#include "y/dft/fmt/_32768.hpp"
#include "y/calculus/alignment.hpp"
#include <cstring>

namespace Yttrium
{
    //! inner real for DFT
    template <typename T> struct DFT_Real        { typedef T      Type; /*!< alias */ };

    //! inner real fo float DFT
    template <>           struct DFT_Real<float> { typedef double Type; /*!< alias */ };


    //__________________________________________________________________________
    //
    //
    //
    //! Discrete Fourier Transform
    //
    //
    //__________________________________________________________________________
    struct DFT
    {

        //______________________________________________________________________
        //
        //
        //! precomputed trigonometric tables
        //
        //______________________________________________________________________
        template <typename T> struct Table
        {
            static const T PositiveSin[64]; //!<  sin(pi/(2^i))
            static const T NegativeSin[64]; //!< -sin(pi/(2^i))
            static const T CosMinusOne[64]; //!< cos(pi/(2^i))-1`
        };

        //______________________________________________________________________
        //
        //
        //! swap two consecutive blocks \param lhs lhs \param rhs rhs
        //
        //______________________________________________________________________
        template <typename T> static inline
        void Swap2(T * const lhs, T * const rhs) noexcept {
            static const size_t           Request = 2 * sizeof(T);
            const void         *          tmp[ Alignment::WordsGEQ<Request>::Count ];
            memcpy(tmp,lhs,Request);
            memcpy(lhs,rhs,Request);
            memcpy(rhs,tmp,Request);
        }

        //______________________________________________________________________
        //
        //
        //! Format using fallback algorithm
        /**
         \param data [1..2*size]
         \param size count of complex numbers
         \return 2*size
         */
        //
        //______________________________________________________________________
        template <typename T> static inline
        size_t Format_(T data[], const size_t size) noexcept
        {
            const size_t n = size << 1;
            for(size_t i=1,j=1;i<n;i+=2)
            {
                if(j>i)
                    Swap2(data+i,data+j);
                size_t m=size;
                while( (m >= 2) && (j > m) )
                {
                    j -= m;
                    m >>= 1;
                }
                j += m;
            }
            return n;
        }

        //______________________________________________________________________
        //
        //
        //! Dual Format using fallback algorithm
        /**
         \param data1 [1..2*size]
         \param data2 [1..2*size]
         \param size count of complex numbers
         \return 2*size
         */
        //
        //______________________________________________________________________
        template <typename T> static inline
        size_t Format_(T data1[], T data2[], const size_t size) noexcept
        {
            const size_t n = size << 1;
            for(size_t i=1,j=1;i<n;i+=2)
            {
                if(j>i)
                {
                    Swap2(data1+i,data1+j);
                    Swap2(data2+i,data2+j);
                }
                size_t m=size;
                while( (m >= 2) && (j > m) )
                {
                    j -= m;
                    m >>= 1;
                }
                j += m;
            }
            return n;
        }

        
    private:
        //! swap indices info from table
        struct SwapInfo {
            uint16_t i; //!< first index
            uint16_t j; //!< second index
        };
    public:

        //______________________________________________________________________
        //
        //
        //! Format using precomputed table
        /**
         \param data matching FMT::Count
         \return FMT::Result
         */
        //
        //______________________________________________________________________
        template <typename T, typename FMT> static inline
        size_t Format(T data[]) noexcept
        {
            static const SwapInfo * const InfoTab = (const SwapInfo *) Memory::Stealth::Address(& FMT::Table[0][0]);
            static const size_t           Request = 2 * sizeof(T);
            void         *                tmp[ Alignment::WordsGEQ<Request>::Count ];

            for(size_t i=0;i<FMT::Count;++i)
            {
                const SwapInfo info = InfoTab[i];
                T * const      lhs  = data+info.i;
                T * const      rhs  = data+info.j;
                memcpy(tmp,lhs,Request);
                memcpy(lhs,rhs,Request);
                memcpy(rhs,tmp,Request);
            }
            return FMT::Result;
        }

        //______________________________________________________________________
        //
        //
        //! Dual Format using precomputed table
        /**
         \param data1 matching FMT::Count
         \param data2 matching FMT::Count
         \return FMT::Result
         */
        //______________________________________________________________________
        template <typename T, typename FMT> static inline
        size_t Format(T data1[], T data2[]) noexcept
        {
            static const SwapInfo * const InfoTab = (const SwapInfo *) Memory::Stealth::Address(& FMT::Table[0][0]);
            static const size_t           Request = 2 * sizeof(T);
            const void         *          tmp[ Alignment::WordsGEQ<Request>::Count ];

            for(size_t i=0;i<FMT::Count;++i)
            {
                const SwapInfo info = InfoTab[i];
                {
                    T * const      lhs  = data1+info.i;
                    T * const      rhs  = data1+info.j;
                    memcpy(tmp,lhs,Request);
                    memcpy(lhs,rhs,Request);
                    memcpy(rhs,tmp,Request);
                }
                {
                    T * const      lhs  = data2+info.i;
                    T * const      rhs  = data2+info.j;
                    memcpy(tmp,lhs,Request);
                    memcpy(lhs,rhs,Request);
                    memcpy(rhs,tmp,Request);
                }
            }
            return FMT::Result;
        }




        //______________________________________________________________________
        //
        //
        //! Format Data Dispatcher
        /**
         \param data user data
         \param size count of complex numbers
         \return size*2
         */
        //
        //______________________________________________________________________
        template <typename T> static inline
        size_t Format(T data[], const size_t size) noexcept
        {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define     Y_DFT_Format(N) case N: return Format<T,DFT_Fmt##N>(data)
#endif
            switch(size)
            {
                    Y_DFT_Format(4);
                    Y_DFT_Format(8);
                    Y_DFT_Format(16);
                    Y_DFT_Format(32);
                    Y_DFT_Format(64);
                    Y_DFT_Format(128);
                    Y_DFT_Format(256);
                    Y_DFT_Format(512);
                    Y_DFT_Format(1024);
                    Y_DFT_Format(2048);
                    Y_DFT_Format(4096);
                    Y_DFT_Format(8192);
                    Y_DFT_Format(16384);
                    Y_DFT_Format(32768);
                default:
                    break;
            }
            return Format_(data,size);
        }


        //______________________________________________________________________
        //
        //
        //! Dual Format Data Disatcher
        /**
         \param data1 user data
         \param data2 user data
         \param size count of complex numbers
         \return size*2
         */
        //
        //______________________________________________________________________
        template <typename T> static inline
        size_t Format(T data1[], T data2[], const size_t size) noexcept
        {
            switch(size)
            {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define             Y_DFT_Format2(N) case N: return Format<T,DFT_Fmt##N>(data1,data2)
#endif
                    Y_DFT_Format2(4);
                    Y_DFT_Format2(8);
                    Y_DFT_Format2(16);
                    Y_DFT_Format2(32);
                    Y_DFT_Format2(64);
                    Y_DFT_Format2(128);
                    Y_DFT_Format2(256);
                    Y_DFT_Format2(512);
                    Y_DFT_Format2(1024);
                    Y_DFT_Format2(2048);
                    Y_DFT_Format2(4096);
                    Y_DFT_Format2(8192);
                    Y_DFT_Format2(16384);
                    Y_DFT_Format2(32768);
                default:
                    break;
            }
            return Format_(data1,data2,size);
        }


#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define Y_DFT_Transform(DATA)                             \
/**/  const T j_re  = DATA[j];                            \
/**/  const T j_im =  DATA[j1];                           \
/**/  const T tempr = static_cast<T>(wr*j_re - wi*j_im);  \
/**/  const T tempi = static_cast<T>(wr*j_im + wi*j_re);  \
/**/  DATA[j]       = DATA[i]  - tempr;                   \
/**/  DATA[j1]      = DATA[i1] - tempi;                   \
/**/  DATA[i]      += tempr;                              \
/**/  DATA[i1]     += tempi
#endif
        //______________________________________________________________________
        //
        //
        //! Transform Using a Sine Table
        /**
         - Replaces data[1..2*size] :
         - by its              Discrete Fourier transform         if SinTable = PositiveSin
         - by 'size' times its Inverse Discrete Fourier transform if SinTable = NegativeSin
         \param data user data
         \param size count of complex numbers
         \param SinTable precomputed sine table
         */
        //______________________________________________________________________
        template <typename T> static inline
        void Transform(T                                data[],
                       const size_t                     size,
                       const typename DFT_Real<T>::Type SinTable[]) noexcept
        {
            typedef typename DFT_Real<T>::Type long_T;
            const  size_t n = Format(data,size);
            size_t mmax=2;
            size_t indx=0;
            while(n>mmax)
            {
                const size_t istep = (mmax << 1);
                long_T       wpr   = Table<long_T>::CosMinusOne[indx];
                long_T       wpi   = SinTable[indx];
                long_T       wr    = 1;
                long_T       wi    = 0;
                for(size_t m=1;m<mmax;m+=2)
                {
                    for(size_t i=m;i<=n;i+=istep)
                    {
                        const size_t j  = i+mmax;
                        const size_t i1 = i+1;
                        const size_t j1 = j+1;
                        { Y_DFT_Transform(data); }
                    }
                    const long_T wt=wr;
                    wr=(wt*wpr-wi*wpi)+wt;
                    wi=(wi*wpr+wt*wpi)+wi;
                }
                mmax=istep;
                ++indx;
            }
        }

        //______________________________________________________________________
        //
        //
        //! Dual Transform Using a Sine Table
        /**
         \param data1 user data
         \param data2 user data
         \param size count of complex numbers
         \param SinTable precomputed sine table
         */
        //______________________________________________________________________
        template <typename T> static inline
        void Transform(T                                data1[],
                       T                                data2[],
                       const size_t                     size,
                       const typename DFT_Real<T>::Type SinTable[]) noexcept
        {
            typedef typename DFT_Real<T>::Type long_T;
            const  size_t n = Format(data1,data2,size);
            size_t mmax=2;
            size_t indx=0;
            while(n>mmax)
            {
                const size_t istep = (mmax << 1);
                long_T       wpr   = Table<long_T>::CosMinusOne[indx];
                long_T       wpi   = SinTable[indx];
                long_T       wr    = 1;
                long_T       wi    = 0;
                for(size_t m=1;m<mmax;m+=2)
                {
                    for(size_t i=m;i<=n;i+=istep)
                    {
                        const size_t j  = i+mmax;
                        const size_t i1 = i+1;
                        const size_t j1 = j+1;
                        { Y_DFT_Transform(data1); }
                        { Y_DFT_Transform(data2); }
                    }
                    const long_T wt=wr;
                    wr=(wt*wpr-wi*wpi)+wt;
                    wi=(wi*wpr+wt*wpi)+wi;
                }
                mmax=istep;
                ++indx;
            }
        }

        //______________________________________________________________________
        //
        //
        //! Forward Discrete Fourier Transform of data[1..2*size]
        /**
         \param data user data
         \param size count of complex numbers
         */
        //______________________________________________________________________
        template <typename T> static inline
        void Forward(T            data[],
                     const size_t size) noexcept
        {
            Transform(data,size,Table< typename DFT_Real<T>::Type >::PositiveSin);
        }

        //______________________________________________________________________
        //
        //
        //! Dual Forward Discrete Fourier Transform of data[1|2][1..2*size]
        /**
         \param data1 user data
         \param data2 user data
         \param size  count of complex numbers
         */
        //______________________________________________________________________
        template <typename T> static inline
        void Forward(T            data1[],
                     T            data2[],
                     const size_t size) noexcept
        {
            Transform(data1,data2,size,Table< typename DFT_Real<T>::Type >::PositiveSin);
        }
        //______________________________________________________________________
        //
        //
        //! Forward Discrete Fourier Transform of cplx[1..size]
        /**
         \param cplx user data
         \param size count of complex numbers
         */
        //______________________________________________________________________
        template <typename T> static inline
        void Forward(Complex<T>   cplx[],
                     const size_t size) noexcept
        {
            Transform( &cplx[1].re - 1,size,Table< typename DFT_Real<T>::Type >::PositiveSin);

        }

        //______________________________________________________________________
        //
        //
        //! Reverse Discrete Fourier Transform of data[1..2*size], times size
        /**
         \param data user data
         \param size count of complex numbers
         */
        //______________________________________________________________________
        template <typename T> static inline
        void Reverse(T            data[],
                     const size_t size) noexcept
        {
            Transform(data,size,Table< typename DFT_Real<T>::Type >::NegativeSin);
        }

        //______________________________________________________________________
        //
        //
        //! Reverse Discrete Fourier Transform of cplx[1..size]
        /**
         \param cplx user data
         \param size count of complex numbers
         */
        //______________________________________________________________________
        template <typename T> static inline
        void Reverse(Complex<T>   cplx[],
                     const size_t size) noexcept
        {
            Transform( &cplx[1].re - 1,size,Table< typename DFT_Real<T>::Type >::NegativeSin);
        }


        //______________________________________________________________________
        //
        //
        //! unpack for fft1[1..2n] info fft1[1..2n] and fft2[1..2n]
        /**
         \param fft1 packed first fft (unpacked)
         \param fft2 output unpacked second fft
         \param n count of complex numbers
         */
        //______________________________________________________________________
        template <typename T> static inline
        void Unpack(T fft1[], T fft2[], const size_t n) noexcept
        {
            static const T half(0.5);

            const size_t nn1 = 1+n;
            const size_t nn2 = nn1 << 1;
            const size_t nn3 = 1+nn2;

            fft2[1]=fft1[2];
            fft1[2]=fft2[2]=0;
            for(size_t j=3;j<=nn1;j+=2)
            {
                const size_t j1  = j+1;
                const size_t j2  = nn2-j;
                const size_t j3  = nn3-j;

                const T      A   = fft1[j];
                const T      B   = fft1[j2];
                const T      rep =  half*(A+B);
                const T      rem =  half*(A-B);
                const T      C   = fft1[j1];
                const T      D   = fft1[j3];
                const T      aip = half*(C+D);
                const T      aim = half*(C-D);

                fft1[j]  =  rep;
                fft1[j1] =  aim;
                fft1[j2] =  rep;
                fft1[j3] = -aim;
                fft2[j]  =  aip;
                fft2[j1] = -rem;
                fft2[j2] =  aip;
                fft2[j3] =  rem;
            }
        }

        //______________________________________________________________________
        //
        //
        //! Unpack for complexes
        /**
         \param fft1 packed/unpacked first fft
         \param fft2 unpacked second fft
         \param n number of complex numbers
         */
        //______________________________________________________________________
        template <typename T> static inline
        void Unpack(Complex<T> fft1[], Complex<T> fft2[], const size_t n) noexcept
        {
            Unpack( &fft1[1].re-1, &fft2[1].re-1, n );
        }


        //______________________________________________________________________
        //
        //
        //! Two Real DFT at once
        /**
         - real data1[1..size] -> fft1[1..2*size]
         - real data2[1..size] -> fft2[1..2*size]
         \param fft1 target first fft
         \param fft2 target second fft
         \param data1 first real data
         \param data2 second real data
         \param n  count of real/complex numbers
         */
        //______________________________________________________________________
        template <typename T> static inline
        void Forward(T fft1[], T fft2[], const T data1[], const T data2[], const size_t n)
        {
            //------------------------------------------------------------------
            //
            // pack
            //
            //------------------------------------------------------------------
            {
                T *       target = fft1;
                const T * source1 = data1;
                const T * source2 = data2;
                for(size_t j=n;j>0;--j)
                {
                    *(++target) = *(++source1);
                    *(++target) = *(++source2);
                }
            }

            //------------------------------------------------------------------
            //
            // transform
            //
            //------------------------------------------------------------------
            Forward(fft1,n);

            //------------------------------------------------------------------
            //
            // unpack
            //
            //------------------------------------------------------------------
            Unpack(fft1,fft2,n);
        }

        //______________________________________________________________________
        //
        //
        //! fft1 *= fft2
        /**
         \param fft1 target [1..2n] array
         \param fft2 rhs    [1..2n] array
         \param n count of complex numbers
         */
        //
        //______________________________________________________________________
        template <typename T> static inline
        void Multiply(T * fft1, const T * fft2, const size_t n) noexcept
        {
            typedef Complex<T> Cplx;

            for(size_t i=n;i>0;--i)
            {
                const Cplx z1(fft1[1],fft1[2]);
                const Cplx z2(fft2[1],fft2[2]);
                const Cplx z = Cplx::MultiAlgo(z1,z2);
                fft2     += 2;
                *(++fft1) = z.re;
                *(++fft1) = z.im;
            }
        }

    private:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define Y_DFT_RealProcess(DATA)         \
/**/ const T d1  = DATA[i1];            \
/**/ const T d2  = DATA[i2];            \
/**/ const T d3  = DATA[i3];            \
/**/ const T d4  = DATA[i4];            \
/**/ const T h1r =  c1*(d1+d3);         \
/**/ const T h1i =  c1*(d2-d4);         \
/**/ const T h2r = -c2*(d2+d4);         \
/**/ const T h2i =  c2*(d1-d3);         \
/**/ DATA[i1] =  h1r + T(wr*h2r-wi*h2i); \
/**/ DATA[i2] =  h1i + T(wr*h2i+wi*h2r); \
/**/ DATA[i3] =  h1r - T(wr*h2r-wi*h2i); \
/**/ DATA[i4] = -h1i + T(wr*h2i+wi*h2r)
#endif

        //! Real FFT
        /**
         \param data user data
         \param c2   transform coefficient
         \param wpr  complex re recursion
         \param wpi  complex im recursion
         \param n    number of real numbers
         */
        template <typename T> static inline
        void RealProcess(T                                data[],
                         const T                          c2,
                         const typename DFT_Real<T>::Type wpr,
                         const typename DFT_Real<T>::Type wpi,
                         const size_t                     n) noexcept
        {
            typedef typename DFT_Real<T>::Type long_T;
            static const T c1 = 0.5;

            long_T wr  = 1.0+wpr;
            long_T wi  = wpi;

            const size_t nq = n>>2;
            const size_t np3=n+3;
            for(size_t i=2;i<=nq;++i)
            {
                const size_t i1 = (i<<1)-1;
                const size_t i2 = i1+1;
                const size_t i3 = np3-i2;
                const size_t i4 = 1+i3;
                {
                    Y_DFT_RealProcess(data);
                }
                const long_T wt = wr;
                wr=(wr*wpr-wi*wpi)+wr;
                wi=(wi*wpr+wt*wpi)+wi;
            }
        }

        //! Two Real FFT at once
        /**
         \param data1 user data
         \param data2 user data
         \param c2   transform coefficient
         \param wpr  complex re recursion
         \param wpi  complex im recursion
         \param n    number of real numbers
         */
        template <typename T> static inline
        void RealProcess(T                                data1[],
                         T                                data2[],
                         const T                          c2,
                         const typename DFT_Real<T>::Type wpr,
                         const typename DFT_Real<T>::Type wpi,
                         const size_t                     n) noexcept
        {
            typedef typename DFT_Real<T>::Type long_T;
            static const T c1 = 0.5;

            long_T wr  = 1.0+wpr;
            long_T wi  = wpi;

            const size_t nq = n>>2;
            const size_t np3=n+3;
            for(size_t i=2;i<=nq;++i)
            {
                const size_t i1 = (i<<1)-1;
                const size_t i2 = i1+1;
                const size_t i3 = np3-i2;
                const size_t i4 = 1+i3;
                { Y_DFT_RealProcess(data1); }
                { Y_DFT_RealProcess(data2); }
                const long_T wt = wr;
                wr=(wr*wpr-wi*wpi)+wr;
                wi=(wi*wpr+wt*wpi)+wi;
            }
        }

    public:

        //______________________________________________________________________
        //
        //
        //! DFT of data[1..n>=2]
        /**
         \param data user data
         \param n    count of real numbers
         */
        //______________________________________________________________________
        template <typename T> static inline
        void RealForward(T            data[],
                         const size_t n) noexcept
        {
            assert(n>=2);
            typedef typename DFT_Real<T>::Type long_T;
            static const T c2 = -0.5;


            //------------------------------------------------------------------
            // prolog
            //------------------------------------------------------------------
            const size_t   nh = n>>1;
            const unsigned ns = ExactLog2(nh);
            Forward(data,nh);

            //------------------------------------------------------------------
            // process
            //------------------------------------------------------------------
            RealProcess(data,c2,Table<long_T>::CosMinusOne[ns],Table<long_T>::PositiveSin[ns],n);

            //------------------------------------------------------------------
            // epilog
            //------------------------------------------------------------------
            {
                const T h1r = data[1];
                data[1] = h1r+data[2];
                data[2] = h1r-data[2];
            }
        }

        //______________________________________________________________________
        //
        //
        //! Dual Real DFT of data1[1..n>=2], data2[1..n]
        /**
         \param data1 user data
         \param data2 user data
         \param n    count of real numbers
         */
        //______________________________________________________________________
        template <typename T> static inline
        void RealForward(T            data1[],
                         T            data2[],
                         const size_t n) noexcept
        {
            assert(n>=2);
            typedef typename DFT_Real<T>::Type long_T;
            static const T c2 = -0.5;


            //------------------------------------------------------------------
            // prolog
            //------------------------------------------------------------------
            const size_t   nh = n>>1;
            const unsigned ns = ExactLog2(nh);
            Forward(data1,data2,nh);

            //------------------------------------------------------------------
            // process
            //------------------------------------------------------------------
            RealProcess(data1,data2,c2,Table<long_T>::CosMinusOne[ns],Table<long_T>::PositiveSin[ns],n);

            //------------------------------------------------------------------
            // epilog
            //------------------------------------------------------------------
            {
                const T h1r = data1[1];
                data1[1] = h1r+data1[2];
                data1[2] = h1r-data1[2];
            }

            {
                const T h1r = data2[1];
                data2[1] = h1r+data2[2];
                data2[2] = h1r-data2[2];
            }
        }


        //______________________________________________________________________
        //
        //
        //! Reverse DFT of data[1..n>=2]
        /**
         \param data user data
         \param n    count of real numbers
         */
        //______________________________________________________________________
        template <typename T> static inline
        void RealReverse(T            data[],
                         const size_t n)
        {
            assert(n>=2);
            typedef typename DFT_Real<T>::Type long_T;
            static const T c1 = 0.5;
            static const T c2 = 0.5;

            //------------------------------------------------------------------
            // prolog
            //------------------------------------------------------------------
            const size_t   nh = n>>1;
            const unsigned ns = ExactLog2(nh);

            //------------------------------------------------------------------
            // process
            //------------------------------------------------------------------
            RealProcess(data,c2,Table<long_T>::CosMinusOne[ns],Table<long_T>::NegativeSin[ns],n);

            //------------------------------------------------------------------
            // epilog
            //------------------------------------------------------------------
            {
                const T h1r = data[1];
                data[1]=c1*(h1r+data[2]);
                data[2]=c1*(h1r-data[2]);
                Reverse(data,nh);
            }
        }






    };

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#if !defined(_MSC_VER)
    template <> const double      DFT:: Table<double>::      PositiveSin[]; //!< decl
    template <> const double      DFT:: Table<double>::      NegativeSin[]; //!< decl
    template <> const double      DFT:: Table<double>::      CosMinusOne[]; //!< decl

    template <> const long double DFT:: Table<long double>:: PositiveSin[]; //!< decl
    template <> const long double DFT:: Table<long double>:: NegativeSin[]; //!< decl
    template <> const long double DFT:: Table<long double>:: CosMinusOne[]; //!< decl
#endif

#endif

}


#endif

