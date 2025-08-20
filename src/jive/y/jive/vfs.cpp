
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
                    switch(part)
                    {
                        case VFS::Entry::Path:
                            if( matching.found(request,ep->path,ep->path)) break;
                            continue;

                        case VFS::Entry::Base:
                            if( matching.found(request,ep->path,ep->path)) break;
                            continue;

                        case VFS::Entry::Ext:
                            if(!ep->ext) continue;
                            if( matching.found(request,ep->path,ep->ext) ) break;
                            continue;

                        default:
                            throw Specific::Exception("_VFS::Apply", "not for %s", VFS::Entry::PartText(part));
                    }
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

        void   _VFS:: Show(const VFS::Entry &entry, void * const)
        {
            std::cerr << "[" << entry << "]" << std::endl;
        }

        void   _VFS:: Display(const VFS::Entry &entry)
        {
            Show(entry,0);
        }

    }

}
