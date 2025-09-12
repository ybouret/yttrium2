
//! \file


#ifndef Y_Chemical_Conservation_Judge_Included
#define Y_Chemical_Conservation_Judge_Included 1


#include "y/chemical/plexus/conservation/act.hpp"
#include "y/chemical/plexus/conservation/broken.hpp"


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
            //! Judge thru an act
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
                explicit Judge(const Act &); //!< setup
                virtual ~Judge() noexcept;   //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! trial
                /**
                 \param xml  output
                 \param Ctop TopLevel concentrations
                 \param Itop TopLevel accumulator
                 */
                void trial(XMLog &xml, XWritable &Ctop, Accumulator &Itop);

            private:
                Y_Disable_Copy_And_Assign(Judge); //!< discarding

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Act &   act;   //!< persistent Act
                BList         blist; //!< broken list
                XAdd          xadd;  //!< inner additions
                const xreal_t zero;  //!< helper

            public:
                Judge *       next;  //!< for list
                Judge *       prev;  //!< for list
            };

        }


    }

}

#endif

