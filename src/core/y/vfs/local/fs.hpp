
//! \file

#ifndef Y_VFS_LocalFS_Included
#define Y_VFS_LocalFS_Included 1


#include "y/vfs/vfs.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Local File System Interface
    //
    //
    //__________________________________________________________________________
    class LocalFS : public Singleton<LocalFS,ClassLockPolicy>, public VFS
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const      CallSign;                        //!< "LocalFS"
        static const Longevity         LifeTime = LifeTimeOf::LocalFS;  //!< lifetime

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void display(std::ostream &, size_t) const;
        
        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual bool      tryRemoveFile(const String &path);
        virtual Scanner * openDirectory(const String &dirName);
        virtual EntryType findEntryType(const String &path, bool &link) const;
        virtual void      makeDirectory(const String &dirName, const bool mayExist);
        virtual bool      tryEraseEmpty(const String &dirName);
        virtual String    getCWD();
        virtual void      setCWD(const String &dirName);

        //! \param dirName directory to search \return searchable directory pattern
        static  String    MakeWin32Path(const String &dirName);

    private:
        Y_Disable_Copy_And_Assign(LocalFS); //!< discarding
        friend class Singleton<LocalFS,ClassLockPolicy>;
        explicit LocalFS() noexcept; //!< setup
        virtual ~LocalFS() noexcept; //!< cleanup

    };
}

#endif

