

//! \file

#ifndef Y_Jive_VFS_Included
#define Y_Jive_VFS_Included 1

#include "y/jive/pattern/matching.hpp"
#include "y/vfs/vfs.hpp"

namespace Yttrium
{
    namespace Jive
    {
        //______________________________________________________________________
        //
        //
        //
        //! Operations on VFS
        //
        //
        //______________________________________________________________________
        struct _VFS
        {
            typedef void (*Proc)(const VFS::Entry &, void * const); //!< alias

            //! prototype, show entry
            static  void   Show(const VFS::Entry &, void * const);

            static  void   Display(const VFS::Entry &);

            //! base call: collect and apply
            /**
             \param scanner new directoy scanner
             \param matching compiled matching
             \param request  matching request
             \param part     entry part to match
             \param proc     procedure to call
             \param args     procedure arguments
             */
            static void Apply(Yttrium::VFS::Scanner * const scanner,
                              Matching &                    matching,
                              const Matching::Request       request,
                              const VFS::Entry::Part        part,
                              Proc const                    proc,
                              void * const                  args);

            //! high level call
            /**
             \param vfs      vfs to use
             \param dirName  directory to open
             \param regexp   regular expression to match
             \param request  matching request
             \param part     entry part to match
             \param proc     proc(entry)
             */
            template <typename DIRNAME, typename REGEXP, typename PROC>
            static inline
            void Apply(VFS &                   vfs,
                       const DIRNAME &         dirName,
                       const REGEXP  &         regexp,
                       const Matching::Request request,
                       const VFS::Entry::Part  part,
                       PROC &                  proc)
            {
                Matching matching = regexp;
                Apply( vfs.openDirectory(dirName), matching, request, part, Wrapper<PROC>, (void*) &proc);
            }

            

        private:
            //! wrapper \param entry found \param args PROC address
            template <typename PROC> static inline
            void Wrapper(const VFS::Entry &entry, void * const args)
            {
                assert(0!=args);
                PROC & proc = *(PROC *)args;
                proc(entry);
            }
        };

    }

}

#endif

