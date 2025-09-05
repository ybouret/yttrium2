#include "y/vfs/vfs.hpp"
#include "y/system/exception.hpp"
#include <cstring>

namespace Yttrium
{

    VFS::Entry:: Entry(VFS &fs, const String &name) :
    Object(),
    vfs(fs),
    path(name),
    base( BaseName(path)  ),
    ext(  Extension(base) ),
    link(false),
    type( vfs.findEntryType(path, Coerce(link)) ),
    next(0),
    prev(0)
    {

    }


    VFS::Entry:: Entry(VFS &fs, const char *name) :
    Object(),
    vfs(fs),
    path( name ),
    base( BaseName(path)  ),
    ext(  Extension(base) ),
    link( false ),
    type( vfs.findEntryType(path, Coerce(link)) ),
    next(0),
    prev(0)
    {

    }

    VFS::Entry:: ~Entry() noexcept
    {
    }

    static inline
    size_t shifting(const char * const field, const String &path)
    {
        assert(0!=field);
        const size_t offset = static_cast<size_t>(field-path.c_str());
        assert(offset<path.size());
        return offset;
    }

    VFS::Entry:: Entry(const Entry &entry) :
    Object(),
    vfs(entry.vfs),
    path(entry.path),
    base(path.c_str() + shifting(entry.base,entry.path)),
    ext(0==entry.ext? 0 : path.c_str() + shifting(entry.ext,entry.path)),
    link(entry.link),
    type(entry.type),
    next(0),
    prev(0)
    {
    }

    const VFS::Entry & VFS::Entry:: operator*() const noexcept { return *this; }

    bool VFS::Entry:: isReg() const noexcept  { return VFS::IsReg == type; }
    bool VFS::Entry:: isDir() const noexcept  { return VFS::IsDir == type; }

    bool VFS:: Entry:: isDot() const
    {
        assert(0!=base);
        if( 1 == strlen(base) && '.' == base[0] )
        {
            if(!isDir()) throw Specific::Exception(CallSign, "'.' is not a directory");
            return true;
        }
        else
        {
            return false;
        }
    }

    bool VFS:: Entry:: isDDot() const
    {
        assert(0!=base);
        if( 2 == strlen(base) && '.' == base[0] && '.' == base[1])
        {
            if(!isDir()) throw Specific::Exception(CallSign, "'..' is not a directory");
            return true;
        }
        else
        {
            return false;
        }
    }


    const char * VFS::Entry:: typeText() const noexcept
    {
        return VFS::EntryTypeText(type);
    }

    const char * const VFS::Entry:: CallSign = "VFS::Entry";
    
    String VFS::Entry:: pry(const Part part) const
    {
        switch(part)
        {
            case Path:   return path;
            case PathWE: return ext ? String(path.c_str(),static_cast<size_t>(ext-path.c_str()) ) : path;
            case Base:   return String(base);
            case BaseWE: return ext ? String(base,static_cast<size_t>(ext-base) ) : String(base);
            case Ext:    return String(ext?ext+1:0);
        }
        throw Specific::Exception(CallSign,"corrupted VFS::Entry::Part value");
    }

#define Y_VFS_ENTRY_PART(NAME) case NAME: return #NAME

    const char * VFS::Entry:: PartText(const Part part) noexcept
    {
        switch(part)
        {
                Y_VFS_ENTRY_PART(Path);
                Y_VFS_ENTRY_PART(PathWE);
                Y_VFS_ENTRY_PART(Base);
                Y_VFS_ENTRY_PART(BaseWE);
                Y_VFS_ENTRY_PART(Ext);
        }
        // never get here
        return Core::Unknown;
    }

    std::ostream & operator<<(std::ostream &os, const VFS::Entry &ep)
    {
        os << '[';
        os << ep.typeText();
        if(ep.link)
        {
            os << '@';
        }
        else
        {
            os << ' ';
        }
        os << ']' << ' ' << ep.path;
        if(ep.ext)
        {
            os << ' ' << '[' << ep.ext << ']';
        }
        return os;
    }

    SignType VFS:: Entry:: CompareByPath(const Entry *lhs, const Entry *rhs) noexcept
    {
        assert(0!=lhs);
        assert(0!=rhs);
        return String::Compare(lhs->path,rhs->path);
    }

    SignType VFS:: Entry:: CompareByName(const Entry *lhs, const Entry *rhs) noexcept
    {
        assert(0!=lhs);
        assert(0!=rhs);
        const int res = strcmp(lhs->base,rhs->base);
        return Sign::Of(res);
    }


    SignType VFS:: Entry::  CompareByPathDirFirst(const Entry *lhs, const Entry *rhs) noexcept
    {
        const int L = EntryTypeChar(lhs->type);
        const int R = EntryTypeChar(rhs->type);

        switch( Sign::Of(L,R) )
        {
            case Negative: return Negative;
            case __Zero__: break;
            case Positive: return Positive;
        }
        return CompareByPath(lhs,rhs);
     }

}


