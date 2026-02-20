
//! \file

#ifndef Y_Ink_Image_Formats_Included
#define Y_Ink_Image_Formats_Included 1

#include "y/ink/image/format.hpp"
#include "y/container/associative/suffix/set.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"

namespace Yttrium
{
    namespace Ink
    {

        typedef SuffixSet<String,Format::Handle> FormatsDB; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Meta-Format
        //
        //
        //______________________________________________________________________
        class Formats :
        public Singleton<Formats,ClassLockPolicy>,
        public FormatsDB,
        public Codec
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign;                          //!< "Ink::Formats"
            static const Longevity    LifeTime = LifeTimeOf::InkFormats; //!< alias

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void  display(std::ostream &, size_t) const;
            virtual void  onSave(const Image  &, const String &, const Options * const) const;
            virtual Image onLoad(const String &, const Options * const)                 const;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void             operator()( Format * const ); //!< register new format
            void             loadBuiltIn();                //!< load built-in formats
            static Formats & Std();                        //!< \return instance with loaded built-in
            const Format   & operator[](const String &path) const; //!< \param path file name \return format for path



        private:
            Y_Disable_Copy_And_Assign(Formats); //!< discarding
            friend class Singleton<Formats,ClassLockPolicy>;
            
            explicit Formats();          //!< setup
            virtual ~Formats() noexcept; //!< cleanup


        };


    }

}

#endif // !Y_Ink_Image_Formats_Included

