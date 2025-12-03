

//! \file

#ifndef Y_Output_Stream_Included
#define Y_Output_Stream_Included 1

#include "y/type/ints.hpp"
#include "y/string/fwd.hpp"
#include "y/check/printf.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Output Stream API
    //
    //
    //__________________________________________________________________________
    class OutputStream
    {
    protected:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit OutputStream() noexcept;

    public:
        virtual ~OutputStream() noexcept;

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        virtual void write(const char)                       = 0; //!< write one char
        virtual void flush()                                 = 0; //!< flush any internal buffer
        virtual void frame(const void * const, const size_t);     //!< write a frame of data


        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! write encoded 64-bits \return number of written bytes
        size_t encode64(const uint64_t);

        //! emit any integral type in Variable Bit Rate
        /**
         \param value value to encode
         \return written bytes
         */
        template <typename T>
        size_t emitVBR(const T &value)
        {
            return encode64( value );
        }

        //! emit integral types with Constant Bit Rate
        /**
         \param value value to write
         \return written bytes, should be sizeof(value)
         */
        template <typename T>
        size_t emitCBR(const T &value)
        {
            union
            {
                T x;
                typename UnsignedIntFor<T>::Result::Type y;
            } alias = { value };
            return emit(alias.y);
        }

        OutputStream & operator<< (const char);                                 //!< helper \return *this
        OutputStream & operator<< (const char * const);                         //!< helper \return *this
        OutputStream & operator<< (const Core::String<char> &);                 //!< helper \return *this

        //! helper \return *this
        OutputStream & operator() (const char * const,...) Y_Printf_Check(2,3);

    private:
        Y_Disable_Copy_And_Assign(OutputStream); //!< discarding
        size_t emit(const uint8_t  &); //!< \return 1 on success
        size_t emit(const uint16_t &); //!< \return 2 on success
        size_t emit(const uint32_t &); //!< \return 4 on success
        size_t emit(const uint64_t &); //!< \return 8 on success

    };
}

#endif // !Y_Output_Stream_Included

