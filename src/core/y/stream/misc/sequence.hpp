

//! \file

#ifndef Y_Output_Sequence_Stream_Included
#define Y_Output_Sequence_Stream_Included 1

#include "y/stream/output.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! convert sequence into OutputStream
    //
    //
    //__________________________________________________________________________
    template <typename SEQUENCE>
    class OutputSequence : public OutputStream
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        //! setup \param seq persistent sequence
        inline explicit OutputSequence( SEQUENCE & seq ) noexcept :
        OutputStream(),
        host(seq)
        {
        }

        //! cleanup
        inline virtual ~OutputSequence() noexcept {}

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual void write(const char c)
        {
            typename SEQUENCE::ConstType value(c);
            host << value;
        }

        inline virtual void flush() {}

    private:
        SEQUENCE & host; //!< persistent
    };

    template <typename SEQUENCE, typename SERIALIZABLE> inline
    void SerializeTo(SEQUENCE &seq, const SERIALIZABLE &src)
    {
        OutputSequence<SEQUENCE> out(seq);
        (void) src.serialize(out);
    }
    


}

#endif
