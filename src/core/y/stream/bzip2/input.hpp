


//! \file
#ifndef Y_BZip2_InputFile_Included
#define Y_BZip2_InputFile_Included 1

#include "y/stream/bzip2/file.hpp"
#include "y/stream/libc/input.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{
    namespace BZip2
    {

        //______________________________________________________________________
        //
        //
        //
        //! BZIP2 Input File
        //
        //
        //______________________________________________________________________
        class InputFile : public File, public InputStream
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            //! setup
            /**
             \param param file name
             \param small optionanl small parameter for bzip2
             */
            template <typename PARAM>
            explicit InputFile(const PARAM & param,
                               const bool small = false) :
            cfp( new Yttrium::InputFile(param) ),
            err(0),
            bzf( setup(small) )
            {
            }

            //! cleanup
            virtual ~InputFile() noexcept;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual bool query(char &);
            virtual void store(const char);

        private:
            Y_Disable_Copy_And_Assign(InputFile); //!< discarding
            ArcPtr<Yttrium::InputFile> cfp;       //!< Libc file pointer
            int                        err;       //!< error code for operations
            void * const               bzf;       //!< BZIP2 handle

            //! setup \param small for bzip2 \return BZIP2 file
            void * setup(const bool small);
        };

    }
}

#endif // !Y_BZip2_InputFile_Included

