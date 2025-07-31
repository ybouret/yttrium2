
//! \file

#ifndef Y_Apex_Ortho_Vector_Included
#define Y_Apex_Ortho_Vector_Included 1

#include "y/ortho/metrics.hpp"
#include "y/container/cxx/array.hpp"
#include "y/apex/rational.hpp"
#include "y/core/linked/list/cxx.hpp"
#include "y/ability/caching.hpp"

namespace Yttrium
{

    namespace Ortho
    {

        //! base type for apz vector
        typedef CxxArray<const apz> VectorType;

        //______________________________________________________________________
        //
        //
        //
        //! vector to form orthogonal basis
        //
        //
        //______________________________________________________________________
        class Vector : public Object, public Metrics, public VectorType
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef CxxListOf<Vector> List; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Vector(const Metrics &);           //!< setup to zero from metrics
            Vector(const Vector &);            //!< duplicate
            virtual ~Vector() noexcept;        //!< cleanup
            Vector & operator=(const Vector&); //!< assign with same dimensions \return *this
            Y_OSTREAM_PROTO(Vector);           //!< display

            //! assign from compatible array (int,apz,apn,apq...) and update
            /**
             \param copyOf helper
             \param arr    array eith positive size
             */
            template <typename ARRAY> inline
            Vector(const CopyOf_ &copyOf, ARRAY &arr) :
            Object(),
            Metrics( arr.size() ),
            VectorType(copyOf,arr),
            ncof(0),
            npos(0),
            nneg(0),
            nrm2(),
            next(0),
            prev(0)
            {
                update();
            }

            //! assign compatible array with same size/metrics
            /**
             \param arr compatible array in type and size
             \return *this, copy and updated
             */
            template <typename ARRAY> inline
            Vector & assign(ARRAY &arr)
            {
                assert(arr.size()==dimensions);
                try {
                    for(size_t i=dimensions;i>0;--i)
                        Coerce( (*this)[i] ) = arr[i];
                }
                catch(...) { ldz(); throw; }
                update();

                return *this;
            }



            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void ldz() noexcept; //!< no-throw clear
            void update();       //!< update to univocal vector
            apz  dot(const Vector &) const; //!< \return *this . vector

            //! test equality
            friend bool operator==(const Vector &, const Vector &) noexcept;

            //! \param b vector to project on \return true is not null after projection
            bool keepOrtho(const Vector &b);

            //! comparison for list \return ncof/nrm2/lexicographic comparison
            static SignType Compare(const Vector * const, const Vector * const) noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t ncof; //!< number of non-zero coefficient(s)
            const size_t npos; //!< number of positive coefficient(s)
            const size_t nneg; //!< number of negative coefficient(s)
            const apn    nrm2; //!< |*this|^2
            Vector *     next; //!< for list/pool
            Vector *     prev; //!< for list

            //__________________________________________________________________
            //
            //
            //! Pool for Families
            //
            //__________________________________________________________________
            class Pool : public Metrics, public Caching
            {
            public:
                //______________________________________________________________
                //
                // C++
                //______________________________________________________________
                explicit Pool(const Metrics &) noexcept; //!< setup
                virtual ~Pool() noexcept;                //!< cleanup

                //______________________________________________________________
                //
                // Interface
                //______________________________________________________________
                virtual size_t count() const noexcept;
                virtual void   cache(const size_t);
                virtual void   gc(const uint8_t) noexcept;

                //______________________________________________________________
                //
                // Methods
                //______________________________________________________________
                Vector * query();                        //!< \return fetched/created vector
                void     store(Vector * const) noexcept; //!< store/clean vector



                //! prepare vector from array
                /**
                 \param arr compatbile array in type and size
                 \return copied and updated vector
                 */
                template <typename ARRAY> inline
                Vector * query(ARRAY &arr)
                {
                    assert(dimensions==arr.size());
                    Vector * const v = query();
                    try {
                        v->assign(arr);
                    }
                    catch(...)
                    {
                        store(v);
                        throw;
                    }
                    return v;
                }

            private:
                Y_Disable_Copy_And_Assign(Pool); //!< discarding
                List list; //!< current cache
            };



        };

        

    }

}

#endif
