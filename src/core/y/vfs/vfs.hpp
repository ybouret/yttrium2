
//! \file

#ifndef Y_VFS_Included
#define Y_VFS_Included 1


#include "y/string.hpp"
#include "y/core/linked/list/cxx.hpp"
#include "y/object.hpp"
#include "y/ability/identifiable.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! VFS Interface
    //
    //
    //__________________________________________________________________________
    class VFS
    {
    public:
        //______________________________________________________________________
        //
        //
        // File Names
        //
        //______________________________________________________________________
        static bool        IsSeparator(const char )                              noexcept; //!< \return true iff [back]slash
        static const char *BaseName(const char * const path, const size_t size)  noexcept; //!< \param path path \param size size \return basename
        static const char *BaseName(const char * const path)                     noexcept; //!< \param path path \return basename
        static const char *BaseName(const String     & path)                     noexcept; //!< \param path path \return basename

        static const char *Extension(const char * const path, const size_t size) noexcept; //!< \param path path \param size size \return NULL or .ext
        static const char *Extension(const char * const path)                    noexcept; //!< \param path path \return NULL or .ext
        static const char *Extension(const String &     path)                    noexcept; //!< \param path path \return NULL or .ext

        //! changing extension
        /**
         \param newExt new extension address
         \param extLen new extension length
         \param path   current path
         \param size   current path length
         \return string with changed extension
         */
        static String ChangedExtension(const char * const newExt,
                                       const size_t       extLen,
                                       const char * const path,
                                       const size_t       size);

        //! \param newExt new extension \param path old path \return path with new extentions
        static String ChangedExtension(const char * const  newExt, const String & path);

        //! \param newExt new extension \param path old path \return path with new extentions
        static String ChangedExtension(const String      & newExt, const String & path);

        //! \param path old path \param size path length \return path with removed extension
        static String RemovedExtension(const char * const path, const size_t size);

        //! \param path old path \return path with remove extension
        static String RemovedExtension(const String& path);


        //______________________________________________________________________
        //
        //
        // Directory Name
        //
        //______________________________________________________________________

        //! make simplified, separator ending directory name
        /**
         \param path full path
         \param size strlen(path)
         \return as directory name
         */
        static String MakeDirName(const char *const path, const size_t size);
        static String MakeDirName(const char *const); //!< alias \return as directory name
        static String MakeDirName(const String &   ); //!< alias \return as directory name


        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char  EmptyName[]; //!< ""

        //! admitted entry type
        enum EntryType
        {
            IsDir, //!< directory
            IsReg, //!< regular file
            IsUnk  //!< doesn't exists ?
        };

        //! integer value to compare entries \return 'f','d' or 'u'
        static int         EntryTypeChar(const EntryType) noexcept;

        //! human readable entry type \return "f", "d', "?" or "!"
        static const char *EntryTypeText(const EntryType) noexcept;

        //______________________________________________________________________
        //
        //
        //! Entry
        //
        //______________________________________________________________________
        class Entry : public Object
        {
        public:
            //______________________________________________________________________
            //
            //! for file name operations
            //______________________________________________________________________
            enum Part
            {
                Path,      //!< use path
                Base,      //!< use base name
                PathWE,    //!< use path without extension
                BaseWE,    //!< use base without extension
                Ext        //!< use extension
            };

            static const char * const CallSign;                      //!< "VFS::Entry"
            static const char *       PartText(const Part) noexcept; //!< \return human readable part name

            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________
            explicit Entry(VFS &, const String &); //!< setup
            explicit Entry(VFS &, const char   *); //!< setup
            virtual ~Entry() noexcept;                   //!< cleanup
            Entry(const Entry &);                        //!< duplicate
            Y_OSTREAM_PROTO(Entry);                      //!< full display
            const Entry & operator*() const noexcept;    //!< access to display \return *this

            //__________________________________________________________________
            //
            // methods
            //__________________________________________________________________
            const char * typeText() const noexcept; //!< \return EntryTypeText(type)
            bool         isReg()    const noexcept; //!< \return type == IsReg
            bool         isDir()    const noexcept; //!< \return type == IsDir
            String       pry(const Part)     const; //!< \return converted to string for ops
            bool         isDot()             const; //!< \return true iff is '.'
            bool         isDDot()            const; //!< \return true iff is '..'

            //! \return lexicographic path comparison
            static SignType CompareByPath(const Entry *, const Entry *) noexcept;

            //! \return lexicographic base comparison
            static SignType CompareByName(const Entry *, const Entry *) noexcept;

            //! \return lexicographic path comparison, directory first
            static SignType CompareByPathDirFirst(const Entry *, const Entry *) noexcept;


            //__________________________________________________________________
            //
            // members
            //__________________________________________________________________
            VFS &               vfs;  //!< access to operation
            const String        path; //!< full   path
            const char  * const base; //!< within path
            const char  * const ext;  //!< within path
            const bool          link; //!< flag for symbolic link
            const EntryType     type; //!< from fs
            Entry              *next; //!< for list
            Entry              *prev; //!< fir list

        private:
            Y_Disable_Assign(Entry); //!< discarding
        };



        //______________________________________________________________________
        //
        //
        //! List of Entries
        //
        //______________________________________________________________________
        typedef CxxListOf<Entry> Entries; //!< alias


        //______________________________________________________________________
        //
        //
        //! Directory Scanner
        //
        //______________________________________________________________________
        class Scanner : public Object
        {
        public:
            virtual       ~Scanner() noexcept;             //!< cleanup
            virtual Entry *get()          = 0;             //!< \return next entry, NULL when done
        protected:
            explicit       Scanner(VFS &,const String &) ; //!< setup
            VFS &          vfs;                            //!< original vfs
            const String   dir;                            //!< original directory

        private:
            Y_Disable_Copy_And_Assign(Scanner); //!< discarding
        };


        class DirectoryChanger;

        //______________________________________________________________________
        //
        //
        //! Directory Changer
        //
        //______________________________________________________________________
        class ChangeDirectory : public Identifiable, public Readable<const String>
        {
        public:
            //------------------------------------------------------------------
            //
            // Definitions
            //
            //------------------------------------------------------------------
            static const char * const CallSign; //!< VFS::ChangeDirectory

            //------------------------------------------------------------------
            //
            // C++
            //
            //------------------------------------------------------------------
            explicit ChangeDirectory( VFS & );        //!< initialize from CWD = root
            virtual ~ChangeDirectory() noexcept;      //!< cleanup
            ChangeDirectory(const ChangeDirectory &); //!< copy current state

            //------------------------------------------------------------------
            //
            // Methods
            //
            //------------------------------------------------------------------
            ChangeDirectory & operator<<(const String &dirName); //!< change working directory \param dirName directory \return *this
            ChangeDirectory & operator<<(const char * const   ); //!< change working directory wrapper \return *this
            ChangeDirectory & up();                              //!< up one dir \return *this
            void              ok();                              //!< check consistency

            //------------------------------------------------------------------
            //
            // Interface
            //
            //------------------------------------------------------------------
            virtual const char *   callSign() const noexcept;
            virtual size_t         size()     const noexcept;

        private:
            Y_Disable_Assign(ChangeDirectory); //!< discarding
            class Code;
            Code *code; //!< inner code
            virtual const String & getItemAt(const size_t) const noexcept;
        };

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual bool      tryRemoveFile(const String &path)                         = 0; //!< \param path file path \return true iif removed file from VFS
        virtual Scanner * openDirectory(const String &dirName)                      = 0; //!< create scanner \param dirName directory \return new scanner
        virtual EntryType findEntryType(const String &path, bool &lnk) const        = 0; //!< get entry attributes
        virtual void      makeDirectory(const String &dirName, const bool mayExist) = 0; //!< create a directory
        virtual bool      tryEraseEmpty(const String &dirName)                      = 0; //!< try to erase an empty directory
        virtual String    getCWD()                                                  = 0; //!< \return current working directory
        virtual void      setCWD(const String &)                                    = 0; //!< set current working directory

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        bool         tryRemoveFile(const char * const);                //!< alias \return true if removed path
        Scanner    * openDirectory(const char * const);                //!< alias \return new directory scanner
        EntryType    findEntryType(const char * const, bool & ) const; //!< alias \return entry type
        void         makeDirectory(const char * const, const bool  );  //!< alias
        bool         tryEraseEmpty(const char * const);                //!< alias \return true if empty directory was removed
        void         createSubDirs(const String &);                    //!< create all requested dirs
        void         createSubDirs(const char * const);                //!< alias
        void         setCWD(const char * const);                       //!< alias

        //! Add Mode to quickly load entries from a directory
        enum AddMode
        {
            AddReg, //!< add regular files only
            AddDir, //!< add directory only BUT dot and ddot
            AddAny  //!< add dir/reg BUT dot and ddot
        };

        void addTo(Entries &, const String &     dirName, const AddMode mode); //!< grow entries \param dirName directory \param mode how
        void addTo(Entries &, const char * const dirName, const AddMode mode); //!< grow entries \param dirName directory \param mode how


        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        virtual ~VFS() noexcept; //!< cleanup
    protected:
        explicit VFS() noexcept; //!< setup
    private:
        Y_Disable_Copy_And_Assign(VFS); //!< discarding
    };
}

#endif
