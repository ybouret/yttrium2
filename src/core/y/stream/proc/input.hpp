//! \file


#ifndef Y_Stream_Proc_Input_Included
#define Y_Stream_Proc_Input_Included 1

#include "y/stream/proc/stream.hpp"
#include "y/stream/input.hpp"
#include "y/stream/output.hpp"
#include "y/stream/io/chars.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Input Process Stream
    //
    //
    //__________________________________________________________________________
    class InputProcess : public ProcessStream, public InputStream
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const How;      //!< "r"
        static const char * const CallSign; //!< "ProcInput"

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit InputProcess(const String &     cmd); //!< start \param cmd command
        explicit InputProcess(const char * const cmd); //!< start \param cmd command
        virtual ~InputProcess() noexcept;              //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual bool query(char & data);   //!< query \param data single chaer \return false = EOS
        virtual void store(const  char) ;  //!< unread a char, using buffer

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! append lines produced by cmd
        /**
         \param lines sequence-like of strings
         \param cmd   input command
         \return lines
         */
        template <typename SEQUENCE,typename COMMAND>
        static SEQUENCE & AppendTo( SEQUENCE &lines, const COMMAND & cmd)
        {
            InputProcess inp( cmd );
            String       line;
            while(inp.gets(line)) lines << line;
            return lines;
        }

        //! redirect to another stream
        /**
         \param fp output stream
         \param cmd input command
         \return fp
         */
        template <typename COMMAND>
        static OutputStream & SendTo(OutputStream &fp, const COMMAND &cmd)
        {
            InputProcess inp( cmd );
            char         chr = 0;
            while(inp.query(chr)) fp << chr;
			fp.flush();
            return fp;
        }

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        IO::Chars buffer; //!< auxiliary I/O buffer to unread chars

    private:
        Y_Disable_Copy_And_Assign(InputProcess); //!< discarding
    };

}

#endif
