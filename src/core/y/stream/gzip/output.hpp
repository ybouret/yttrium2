

//! \file
#ifndef Y_GZIP_Output_Included
#define Y_GZIP_Output_Included 1

#include "y/stream/output.hpp"
#include "y/stream/gzip/file/output.hpp"
#include "y/string.hpp"

namespace Yttrium
{
    namespace GZip
    {
        //______________________________________________________________________
        //
        //
        //
        //! gzFile as outpit stream
        //
        //
        //______________________________________________________________________
        class Output : public OutputFile, public OutputStream
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! open gzip output stream
            /**
             \param fileName file name
             \param level    in 0:9
             \param append   open in append mode if true
             */
            explicit Output(const char * const fileName, const unsigned level, const bool append=false);
            explicit Output(const String &, const unsigned , const bool=false);     //!< open input file, wrappe
            virtual ~Output() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void write(const char);
            virtual void flush();


        private:
            Y_Disable_Copy_And_Assign(Output); //!< discarding
        };
    }

}

#endif

