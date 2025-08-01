//! \file
//!
#ifndef Y_Coven_Survey_Included
#define Y_Coven_Survey_Included 1

#include "y/coven/types.hpp"
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
            explicit Survey() noexcept;

            //! cleanup
            virtual ~Survey() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void release() noexcept;                  //!< delete vectors, calls=0;
            void reclaim(QVector::Pool &) noexcept;   //!<  store vectors, calls=0

            void collect(XMLog &,const QVector &, QVector::Pool &); //!< collect vector, no duplicate

            //! test equality, mostly to debug
            friend bool operator==(const Survey &, const Survey &) noexcept;


            //! retain vector
            /**
             \param xml to display
             \param keep keep vector if result is true
             \return kept vectors count
             */
            template <typename IS_OK> inline
            size_t retain(XMLog &xml, IS_OK &keep)
            {
                {
                    QVector::List ok;
                    QVector::List bad;
                    while(list.size>0)
                    {
                        const QVector &v = *list.head;
                        if(keep( *list.head ))
                        {
                            Y_XMLog(xml, "[+] " << v);
                            ok.pushTail( list.popHead() );
                        }
                        else
                        {
                            if(xml.verbose)
                                bad.pushTail(list.popHead());
                            else
                                delete list.popHead();
                        }
                    }
                    list.swapListFor(ok);
                    if(xml.verbose && bad.size)
                    {
                        Y_XMLog(xml, "(*) excluded:");
                        while(bad.size)
                        {
                            Y_XMLog(xml,"[-] " << *bad.head);
                            delete bad.popHead();
                        }
                    }
                }
                return list.size;
            }

            


        private:
            Y_Disable_Copy_And_Assign(Survey); //!< discarding
            virtual ConstInterface & locus() const noexcept;

            QVector::List   list; //!< current list

        public:
            const size_t    calls; //!< current calls
        };
    }

}

#endif

