
//! \file


#ifndef Y_Chemical_Conservation_Law_Included
#define Y_Chemical_Conservation_Law_Included 1


#include "y/chemical/reactive/actors.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            typedef CxxArray<unsigned> Weights; //!< alias

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

                //! \return positive excess if any
                xreal_t excess(XAdd &, const XReadable &, const Level) const;

                //! GraphViz with color \return output stream
                OutputStream & viz(OutputStream &, const String &) const;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Weights alpha; //!< compiled weights
                const xreal_t zero;  //!< for computations
                Law *         next;  //!< for list
                Law *         prev;  //!< for list
                
            private:
                Y_Disable_Copy_And_Assign(Law); //!< discarding
            };



        }
    }

}

#endif

