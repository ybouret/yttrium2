#include "y/vfs/vfs.hpp"
#include "y/container/sequence/list.hpp"
#include "y/type/destroy.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace
    {
        //typedef Small::SoloHeavyList<const String> DirList;
        typedef List<const String> DirList;
    }

    const char * const VFS:: ChangeDirectory:: CallSign = "VFS::ChangeDirectory";

    class VFS::ChangeDirectory::Code : public Object, public DirList
    {
    public:
        //! setup with cwd from vfs
        inline explicit Code(VFS &_) :  Object(), DirList(), vfs(_)
        {
            (*this) << vfs.getCWD();
        }

        //! copy other state
        inline explicit Code(const Code &other) : Container(), Object(), DirList(other), vfs(other.vfs) {}

        //! cleanup
        inline virtual ~Code() noexcept {}

        //! check
        inline void check()
        {
            if(size()<=0)
                throw Specific:: Exception(CallSign, "empty state!!!");
            const String & last = tail();
            const String   here = vfs.getCWD();
            if(last!=here) throw Specific::Exception(CallSign, "in '%s'!='%s'", here.c_str(), last.c_str());
        }


        VFS &vfs; //! user's persistent vfs


    private:
        Y_Disable_Assign(Code);
    };

    VFS:: ChangeDirectory:: ChangeDirectory(VFS &vfs) :
    Readable<const String>(),
    code( new Code(vfs) )
    {
    }


    VFS:: ChangeDirectory:: ChangeDirectory(const ChangeDirectory &other) :
    Container(),
    Readable<const String>(),
    code( new Code( *other.code) )
    {
    }


    VFS:: ChangeDirectory:: ~ChangeDirectory() noexcept
    {
        assert(0!=code);
        Destroy(code);
    }


    VFS::ChangeDirectory & VFS::ChangeDirectory:: operator<<(const String &dirName)
    {
#if 1
        assert(0!=code);

        // check and get 'old' directory
        ok();
        const String &old = code->tail();;
        VFS          &vfs = code->vfs;

        // change to new directory
        vfs.setCWD(dirName);
        try {
            const String cwd = vfs.getCWD(); // get system cwd
            (*code) << cwd;                  // add it
        }
        catch(...)
        {
            // try to failsafe
            code->vfs.setCWD(old);
            throw;
        }
#endif
        return *this;
    }

    VFS::ChangeDirectory & VFS::ChangeDirectory:: operator<<(const char * const  dirName)
    {
        const String _(dirName);
        return (*this) << _;
    }

    const char *   VFS:: ChangeDirectory :: callSign() const noexcept { return CallSign; }

    size_t         VFS:: ChangeDirectory :: size()     const noexcept
    {
        assert(0!=code);
        return code->size();
    }

#if 0
    const String & VFS:: ChangeDirectory :: operator[](const size_t iDir) const noexcept
    {
#if 1
        assert(iDir>0);
        assert(iDir<=code->size());
        return **((**code).fetch(iDir));
#endif
    }
#endif
    const String & VFS:: ChangeDirectory:: getItemAt(const size_t iDir) const noexcept
    {
        assert(iDir>0);
        assert(iDir<=code->size());
        return **((**code).fetch(iDir));
    }


    void VFS::ChangeDirectory:: ok()
    {
        assert(0!=code);
        code->check();
    }

    VFS::ChangeDirectory & VFS::ChangeDirectory:: up()
    {
#if 1
        ok();
        if(code->size()>1)
        {
            const String &dirName = **( (**code).tail->prev );
            code->vfs.setCWD(dirName);
            code->popTail();
        }
#endif
        return *this;
    }

}
