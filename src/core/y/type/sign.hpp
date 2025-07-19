//! \file

#ifndef Y_Type_Sign_Included
#define Y_Type_Sign_Included 1

#include "y/type/args.hpp"
#include <cassert>

namespace Yttrium
{

    template <typename> class XReal;

    namespace Core
    {


        //! utility to facilitate cast
        template <typename> struct NeedZeroCast;

        //! XReal<...> need cast
        template <typename T> struct NeedZeroCast< XReal<T> >
        {
            enum { Value = true /*!< true */ };
        };


        //! other types don't need cast
        template <typename T> struct NeedZeroCast
        {
            enum { Value = false /*!< false */};
        };

    }

    //! Named Sign
    enum SignType
    {
        Negative = -1, //!< named negative value
        __Zero__ =  0, //!< named zero value
        Positive =  1  //!< named positive value
    };


    //! operations on signs
    struct Sign
    {
        static const char * HumanReadable(const SignType)     noexcept; //!< named value \return C string
        static bool         StriclyIncreasing(const SignType) noexcept; //!< check \return true for Negative
        static bool         LooselyIncreasing(const SignType) noexcept; //!< check \return true for Negative|__Zero__
        static bool         StriclyDecreasing(const SignType) noexcept; //!< check \return true for Positive
        static bool         LooselyDecreasing(const SignType) noexcept; //!< check \return true for Positive|__Zero__

        //! opposite sign \return hard-coded oppositve
        static SignType Opposite(const SignType) noexcept;

        //! make opposite
        static void MakeOpposite(SignType &) noexcept;

        //! check opposite \return true if NP or PN
        static bool AreOpposite(const SignType,const SignType) noexcept;

        //! natural sign
        /** \param value to be tested \return sign of value againt "0" */
        template <typename T> static inline
        SignType Of(const T &value)
        {
            static const IntToType<Core::NeedZeroCast<T>::Value> NeedCast = {};
            return Of(value,NeedCast);
        }

        //! \param value \return value<0
        template <typename T> static inline
        bool LTZ(const T &value)
        {
            static const IntToType<Core::NeedZeroCast<T>::Value> NeedCast = {};
            return LTZ(value,NeedCast);
        }

        //! \param value \return value<=0
        template <typename T> static inline
        bool LEQZ(const T &value)
        {
            static const IntToType<Core::NeedZeroCast<T>::Value> NeedCast = {};
            return LEQZ(value,NeedCast);
        }

        //! \param value \return value<0
        template <typename T> static inline
        bool GTZ(const T &value)
        {
            static const IntToType<Core::NeedZeroCast<T>::Value> NeedCast = {};
            return GTZ(value,NeedCast);
        }

        //! \param value \return value<0
        template <typename T> static inline
        bool GEQZ(const T &value)
        {
            static const IntToType<Core::NeedZeroCast<T>::Value> NeedCast = {};
            return GEQZ(value,NeedCast);
        }

    private:
        //! \param value \return value<0 without cast
        template <typename T> static inline
        bool LTZ(const T &value, const IntToType<false> &)
        {
            return value<0;
        }

        //! \param value \return value<0 with cast
        template <typename T> static inline
        bool LTZ(const T &value, const IntToType<true> &)
        {
            const T zero;
            return value<zero;
        }

        //! \param value \return value<=0 without cast
        template <typename T> static inline
        bool LEQZ(const T &value, const IntToType<false> &)
        {
            return value<=0;
        }

        //! \param value \return value<=0 with cast
        template <typename T> static inline
        bool LEQZ(const T &value, const IntToType<true> &)
        {
            const T zero;
            return value<=zero;
        }

        //! \param value \return value<0 without cast
        template <typename T> static inline
        bool GTZ(const T &value, const IntToType<false> &)
        {
            return value>0;
        }

        //! \param value \return value<0 with cast
        template <typename T> static inline
        bool GTZ(const T &value, const IntToType<true> &)
        {
            const T zero;
            return value>zero;
        }


        //! \param value \return value>=0 without cast
        template <typename T> static inline
        bool GEQZ(const T &value, const IntToType<false> &)
        {
            return value>0;
        }

        //! \param value \return value>=0 with cast
        template <typename T> static inline
        bool GEQZ(const T &value, const IntToType<true> &)
        {
            const T zero;
            return value>zero;
        }



        //! \param value \return its sign without cast
        template <typename T> static inline SignType Of(const T &value, const IntToType<false> &)
        {
            return value<0 ? Negative : (0<value ? Positive : __Zero__ );
        }

        //! \param value \return its sign with internal  cast
        template <typename T> static inline SignType Of(const T &value, const IntToType<true> &)
        {
            const T zero;
            return value<zero ? Negative : (zero<value ? Positive : __Zero__ );
        }

    public:
        //! natural comparison
        /**
         \param lhs lhs
         \param rhs rhs
         \return sign relying on '<' operator
         */
        template <typename T> static inline
        SignType Of(const T &lhs, const T &rhs)
        {
            return (lhs < rhs) ? Negative : ( (rhs<lhs) ? Positive : __Zero__ );
        }

        //! Increasing Comparison
        /**
         \param lhs address of left object
         \param rhs address of right object
         \return integer comparison
         */
        template <typename T> static inline
        SignType Increasing(const T &lhs, const T rhs) noexcept
        {
            return Of(lhs,rhs);
        }


        //! Decreasing Comparison
        /**
         \param lhs address of left object
         \param rhs address of right object
         \return integer comparison
         */
        template <typename T> static inline
        SignType Decreasing(const T &lhs, const T rhs) noexcept
        {
            return Of(rhs,lhs);
        }

        //! default comparator class
        template <typename T>
        struct Comparator
        {
            Y_Args_Expose(T,Type); //!< aliases

            //! \param lhs lhs \param rhs rhs \return natural comparison
            inline SignType operator()(ConstType &lhs, ConstType &rhs) const
            {
                return Of(lhs,rhs);
            }
        };

        //! default decreasing comparator class
        template <typename T>
        struct DecreasingComparator
        {
            Y_Args_Expose(T,Type); //!< aliases

            //! \param lhs lhs \param rhs rhs \return opposite natural comparison
            inline SignType operator()(ConstType &lhs, ConstType &rhs) const
            {
                return Of(rhs,lhs);
            }
        };


        //! PairType naming
        enum PairType
        {
            NN, //!< Negative/Negative
            NZ, //!< Negative/__Zero__
            NP, //!< Negative/Positive

            ZN, //!< __Zero__/Negative
            ZZ, //!< __Zero__/__Zero__
            ZP, //!< __Zero__/Positive

            PN, //!< Positive/Negative
            PZ, //!< Positive/__Zero__
            PP  //!< Positive/Positive
        };

        //! \return PairType from two signs
        static PairType Pair(const SignType, const SignType) noexcept;


    };
}

#endif

