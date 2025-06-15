
//! \file

#ifndef Y_Input_Stream_Included
#define Y_Input_Stream_Included 1

#include "y/stream/io/chars.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Input Stream API
    //
    //
    //__________________________________________________________________________
    class InputStream
    {
    protected:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit InputStream() noexcept; //!< setup

    public:
        virtual ~InputStream() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual bool query(char &)     = 0; //!< \return true if one char was read
        virtual void store(const char) = 0; //!< unread a char

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! codec64 decoding, throw exception on error
        void decode64(uint64_t &);

        //! read Constant Bit Rate variable
        /**
         \param  value output
         \return number of read bytes
         */
        template <typename T> inline
        size_t readCBR(T &value)
        {
            union
            {
                typename UnsignedIntFor<T>::Result::Type y;
                T x;
            } alias = { 0 };
            const size_t res = read(alias.y);
            value = alias.x;
            return res;
        }

    private:
        Y_Disable_Copy_And_Assign(InputStream); //!< discarding
        size_t read(uint8_t  &); //!< \return [0:1] and value
        size_t read(uint16_t &); //!< \return [0:2] and value
        size_t read(uint32_t &); //!< \return [0:4] and value
        size_t read(uint64_t &); //!< \return [0:8] and value
    };
}

#endif

