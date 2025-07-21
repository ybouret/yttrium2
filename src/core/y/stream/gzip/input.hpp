
//! \file
#ifndef Y_GZIP_Input_Included
#define Y_GZIP_Input_Included 1

#include "y/stream/input.hpp"
#include "y/stream/gzip/file/input.hpp"
#include "y/stream/io/chars.hpp"
#include "y/string.hpp"

namespace Yttrium
{
    namespace GZip
    {
        //______________________________________________________________________
        //
        //
        //
        //! gzFile as input stream
        //
        //
        //______________________________________________________________________
        class Input : public InputFile, public InputStream
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Input(const char * const); //!< open input file
            explicit Input(const String &);     //!< open input file
            virtual ~Input() noexcept;          //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual bool query(char &);
            virtual void store(const char);


        private:
            Y_Disable_Copy_And_Assign(Input); //!< discarding
            IO::Chars buffer; //!< for local caching
        };
    }

}

#endif

