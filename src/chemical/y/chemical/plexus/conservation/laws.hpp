

//! \file


#ifndef Y_Chemical_Conservation_Laws_Included
#define Y_Chemical_Conservation_Laws_Included 1


#include "y/chemical/plexus/conservation/law.hpp"
#include "y/chemical/type/assembly.hpp"
#include "y/graphviz/color-scheme.hpp"
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
            //! Conservation Laws
            //
            //
            //__________________________________________________________________
            class Laws : public Object, public Ingress< const Core::ListOf<Law> >, public Assembly
            {
            public:
                static const char * const CSID; //!< "paired10"
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Laws(XMLog         & xml,
                              const uMatrix & cmatrix,
                              const SList   & species,
                              const EList &   primary,
                              const iMatrix & topology); //!< setup
                virtual ~Laws() noexcept;       //!< cleanup

                //______________________________________________________________
                //
                //
                // Method
                //
                //______________________________________________________________

                //! species available by other means \return output streeam
                OutputStream & viz(OutputStream &) const;

                //! \return true iff species if found in laws
                bool got(const Species &) const noexcept;

#if 0
                //! \param Caux aux-level array \param Ctop top-level array
                void dowload(XWritable &Caux, const XReadable &Ctop) const;

                //! \param Caux aux-level array \param Ctop top-level array
                void upload(XWritable &Ctop, const XReadable &Caux) const;
#endif
                
            private:
                Y_Disable_Copy_And_Assign(Laws);    //!< discarding
                Y_Ingress_Decl();                   //!< helper
                CxxListOf<Law>                list; //!< laws
            public:
                //const SList                   clan; //!< used species
                const size_t                  rank; //!< maximum rank
                const GraphViz::ColorScheme & cs;   //!< color scheme
            };

        }

    }

}

#endif

