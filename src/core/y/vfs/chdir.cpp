#include "y/vfs/vfs.hpp"
//#include "y/data/small/heavy/list/solo.hpp"
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
            //(*this) << vfs.getCWD();
        }

        //! copy other state
        inline explicit Code(const Code &other) : Object(), DirList(other), vfs(other.vfs) {}

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
        Y_DISABLE_ASSIGN(Code);
    };

    VFS:: ChangeDirectory:: ChangeDirectory(VFS &vfs) :
    Identifiable(),
    Collection(),
    Readable<const String>(),
    code( new Code(vfs) )
    {
        std::cerr << "sizeof(Code)=" << sizeof(Code) << std::endl;
    }


    VFS:: ChangeDirectory:: ChangeDirectory(const ChangeDirectory &other) :
    Identifiable(),
    Collection(),
    Readable<const String>(),
    code( new Code( *other.code) )
    {
    }


    VFS:: ChangeDirectory:: ~ChangeDirectory() noexcept
    {
        assert(0!=code);
        Nullify(code);
    }


    VFS::ChangeDirectory & VFS::ChangeDirectory:: operator<<(const String &dirName)
    {
        assert(0!=code);
        assert(0!=code->tail);

        // check and get 'old' directory
        ok();
        const String &old = **(code->tail);
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

        return *this;
    }

    VFS::ChangeDirectory & VFS::ChangeDirectory:: operator<<(const char * const  dirName)
    {
        const String _(dirName);
        return (*this) << _;
    }

    const char *   VFS:: ChangeDirectory :: callSign() const noexcept { return CallSign; }
    size_t         VFS:: ChangeDirectory :: size()     const noexcept { assert(0!=code); return code->size; }
    const String & VFS:: ChangeDirectory :: operator[](const size_t iDir) const noexcept
    {
        assert(iDir>0);
        assert(iDir<=code->size);
        return **(code->fetch(iDir));
    }



    void VFS::ChangeDirectory:: ok()
    {
        assert(0!=code);
        code->check();
    }

    VFS::ChangeDirectory & VFS::ChangeDirectory:: up()
    {
        ok();
        if(code->size>1)
        {
            const String &dirName = **(code->tail->prev);
            code->vfs.setCWD(dirName);
            code->cutTail();
        }
        return *this;
    }

}
