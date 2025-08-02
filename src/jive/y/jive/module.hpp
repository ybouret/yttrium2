
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

            template <typename NAME>
            static Module * OpenFile(const NAME &name)
            {
                const Tag   tag(CopyOf,name);
                const Input inp( OpenFile_(*tag) );
                return new Module(tag,inp);
            }


            //! read char with automatic dot()
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

        };
    }

}

#endif

