

//! \file


#ifndef Y_Chemical_Conservation_Judge_Included
#define Y_Chemical_Conservation_Judge_Included 1


#include "y/chemical/plexus/conservation/laws.hpp"
#include "y/protean/coop/heavy/list.hpp"
#include "y/ortho/house.hpp"
#include "y/mkl/algebra/lu.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {
            //__________________________________________________________________
            //
            //
            //
            //! Broken Law
            //
            //
            //__________________________________________________________________
            class Broken
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                Broken(const Law &, const xreal_t) noexcept; //!< setup
                Broken(const Broken &) noexcept;             //!< duplicate
                ~Broken() noexcept;                          //!< cleanup
                Y_OSTREAM_PROTO(Broken);                     //!< display

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Law &law; //!< broken law
                xreal_t    xs;  //!< excess

            private:
                Y_Disable_Assign(Broken); //!< discarding
            };

            typedef Protean::CoopHeavyList<Broken> BList; //!< alias
            typedef BList::NodeType                BNode; //!< alias
            typedef BList::PoolType                BPool; //!< alias

            //__________________________________________________________________
            //
            //
            //
            //! Judge
            //
            //
            //__________________________________________________________________
            class Judge : public Object
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Judge(const Laws &); //!< setup
                virtual ~Judge() noexcept;    //!< clenup

                void abide(XMLog &xml, XWritable &Ctop);


            private:
                Y_Disable_Copy_And_Assign(Judge); //!< discarding
                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Laws &         laws; //!< origin laws
                const xreal_t        zero; //!< default value
                BPool                bpool; //!< pool
                BList                blist; //!< list of broken laws
                BList                basis; //!< basis of broken laws
                Ortho::House         house; //!< extract basis
                XAdd                 xadd;  //!< inner add
                Cameo::Addition<apz> iadd;
                XArray               Caux;  //!< auxiliary concentration
                MKL::LU<apq>         lu;    //!< inner algebra
                Matrix<apz>          Prj;   //!< Projection row vectors
                CxxArray<apz>        den;   //!< denominator for each projection vector
            };
        }

    }

}

#endif

