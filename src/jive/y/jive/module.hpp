
//! \file

#ifndef Y_Jive_Module_Included
#define Y_Jive_Module_Included 1

#include "y/jive/char.hpp"
#include "y/stream/input.hpp"

namespace Yttrium
{
    namespace Jive
    {


        //______________________________________________________________________
        //
        //! InputStream to Input
        //______________________________________________________________________
        typedef ArcPtr<InputStream> Input;

        //______________________________________________________________________
        //
        //
        //
        //! convert input of char into input of Char
        //
        //
        //______________________________________________________________________
        class Module : public CountedObject, public Context
        {
        public:
            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! OpenFile
            /**
             \param name file name
             \return module with file name
             */
            template <typename NAME>
            static Module * OpenFile(const NAME &name)
            {
                const Tag   tag(name);
                const Input inp( OpenFile_(*tag) );
                return new Module(tag,inp);
            }

            //! OpenData
            /**
             \param name  data name
             \param entry data entry
             \param count data byte count
             \return module with data name
             */
            template <typename NAME>
            static Module * OpenData(const NAME &name, const void * const entry, const size_t count)
            {
                const Tag   tag(name);
                const Input inp( OpenData_(entry,count) );
                return new Module(tag,inp);
            }

            //! OpenData
            /**
             \param name  data name
             \param buffer data
             \return module with file name
             */
            template <typename NAME>
            static Module * OpenData(const NAME &name, const Memory::ReadOnlyBuffer &buffer)
            {
                const Tag   tag(name);
                const Input inp( OpenData_(buffer.ro(), buffer.length()) );
                return new Module(tag,inp);
            }

            



            //! read char with automatic dot() \return NULL if EOF, new char otherwise
            Char *query();


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            virtual ~Module() noexcept; //!< cleanup
        private:
            Y_Disable_Copy_And_Assign(Module); //!< discarding
            explicit Module(const Tag &, const Input &) noexcept; //!< setup

            Input input; //!< input pointer for reading

            //! \return Libc::InputFile
            static InputStream * OpenFile_(const String &);

            //! \return MemoryInput
            static InputStream * OpenData_(const void * const, const size_t);

        };
    }

}

#endif

