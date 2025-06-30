
//! \file

#ifndef Y_Input_Stream_Included
#define Y_Input_Stream_Included 1

#include "y/stream/io/chars.hpp"
#include "y/string/fwd.hpp"

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
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char LF = '\n'; //!< alias
        static const char CR = '\r'; //!< alias

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

        //! codec64 decoding, throw exception on error, with optional variable name
        void decode64(uint64_t &, const char * const  = 0);

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

        //! read Variable Bit Rate variable
        /**
         \param varName optional variable name
         \param varPart optional variable part
         \return T checked value
         */
        template <typename T> inline
        T readVBR(const char * const varName = 0,
                  const char * const varPart = 0)
        {
            static const uint64_t mx = uint64_t(IntegerFor<T>::Maximum);
            uint64_t qw = 0;
            decode64(qw);
            if(qw>mx)
                throwOverflow(varName,varPart,qw,mx);
            return T(qw);
        }

        //! parse line \param line target string \return true if line was found
        bool gets(Core::String<char> &line);


    private:
        Y_Disable_Copy_And_Assign(InputStream); //!< discarding
        size_t read(uint8_t  &); //!< \return [0:1] and value
        size_t read(uint16_t &); //!< \return [0:2] and value
        size_t read(uint32_t &); //!< \return [0:4] and value
        size_t read(uint64_t &); //!< \return [0:8] and value

        //! throw overflow from readVBR
        void throwOverflow(const char * const,
                           const char * const,
                           const uint64_t,
                           const uint64_t) const;
    };
}

#endif

