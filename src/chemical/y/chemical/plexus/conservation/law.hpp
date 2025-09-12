
//! \file


#ifndef Y_Chemical_Conservation_Law_Included
#define Y_Chemical_Conservation_Law_Included 1


#include "y/chemical/reactive/actors.hpp"
#include "y/stream/xmlog.hpp"

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
            //! Conservation Law
            //
            //
            //__________________________________________________________________
            class Law : public Actors, public Vizible
            {
            public:

                class Projection : public Object
                {
                public:
                    explicit Projection(const size_t);
                    virtual ~Projection() noexcept;

                    const XMatrix numer;
                    const XArray  denom;

                    void compute(const Actors & law,
                                 XAdd         & xadd,
                                 XWritable    & Ctop,
                                 XWritable    & Ctmp) const;

                private:
                    Y_Disable_Copy_And_Assign(Projection);
                };

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Law();           //!< setup
                virtual ~Law() noexcept;  //!< cleanup
                Y_OSTREAM_PROTO(Law);     //!< display

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                void finalize(); //!< finalize metrics

                //! \return positive excess if any
                xreal_t excess(XAdd &, const XReadable &, const Level) const;

                //! GraphViz with color \return output stream
                OutputStream & viz(OutputStream &, const String &) const;

                void project(XAdd        & xadd,
                             XWritable   & Ctop,
                             XWritable   & Ctmp) const;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const AutoPtr<Projection> prj;
                const unsigned            ua2;   //!< |*this|^2, unsigned
                const xreal_t             xa2;   //!< |*this|^2, xreal_t
                const xreal_t             norm;  //!< |*this| = sqrt(xa2)
                const xreal_t             zero;  //!< for computations
                Law *                     next;  //!< for list
                Law *                     prev;  //!< for list

            private:
                Y_Disable_Copy_And_Assign(Law); //!< discarding
            };

            typedef Protean::BareLightList<const Law> LList; //!< alias
            typedef LList::NodeType                   LNode; //!< alias


        }
    }

}

#endif

