
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

        typedef SuffixSet<String,Format::Handle> FormatsDB;
        
        class Formats :
        public Singleton<Formats,ClassLockPolicy>,
        public FormatsDB,
        public Codec
        {
        public:
            static const char * const CallSign;
            static const Longevity    LifeTime = LifeTimeOf::InkFormats;

            void             operator()( Format * const ); //!< register new format
            void             loadBuiltIn();                //!< load built-in formats
            static Formats & Std();                        //!< \return instance with loaded built-in
            const Format   & operator[](const String &path) const;

            // interface
            virtual void  display(std::ostream &, size_t) const;
            virtual void  save(const Image  &, const String &, const Options * const) const;
            virtual Image load(const String &, const Options * const)                 const;

        private:
            Y_Disable_Copy_And_Assign(Formats);
            friend class Singleton<Formats,ClassLockPolicy>;
            
            explicit Formats();
            virtual ~Formats() noexcept;
        };


    }

}

#endif // !Y_Ink_Image_Formats_Included

