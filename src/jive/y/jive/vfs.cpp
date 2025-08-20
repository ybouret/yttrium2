
#include "y/jive/vfs.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{
    namespace Jive
    {

        void _VFS:: Apply(Yttrium::VFS::Scanner * const scanner,
                          Matching &                    matching,
                          const Matching::Request       request,
                          const VFS::Entry::Part        part,
                          Proc const                    proc,
                          void * const                  args)
        {
            VFS::Entries                   elist;

            // collecting
            {
                AutoPtr<Yttrium::VFS::Scanner> guard(scanner);
                while(Yttrium::VFS::Entry *_ = scanner->get())
                {
                    AutoPtr<Yttrium::VFS::Entry> ep(_);
                    if(ep->isDot() || ep->isDDot()) continue;
                    const String data = ep->pry(part);
                    if( ! matching.found(request,ep->path,data) ) continue;
                    elist.pushTail(ep.yield());
                }
            }

            // processing
            if(proc)
                while(elist.size)
                {
                    AutoPtr<VFS::Entry> ep = elist.popHead();
                    proc(*ep,args);
                }
        }

        void   _VFS:: Show(VFS::Entry &entry, void * const)
        {
            std::cerr << "[" << entry << "]" << std::endl;
        }

        void   _VFS:: Display(VFS::Entry &entry)
        {
            Show(entry,0);
        }

        void   _VFS:: Remove(VFS::Entry &entry)
        {
            entry.vfs.tryRemoveFile(entry.path);
        }
        

    }

}
