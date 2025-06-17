//! \file

#ifndef Y_UTF8_Included
#define Y_UTF8_Included 1


#include "y/container/readable.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! UTF8/ASCII conversion
    //
    //
    //__________________________________________________________________________
    struct UTF8
    {
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const CallSign;        //!< "UTF-8"
        static const uint8_t BulkInfo = 0x80;      //!< for byte 2-4
        static const uint8_t BulkMask = 0xC0;      //!< of byte 2-4
        static const uint8_t BulkData = 0xFF-0xC0; //!< data from byte 2-4

        //______________________________________________________________________
        //
        //
        //! data for code points range
        //
        //______________________________________________________________________
        struct CodePoints
        {
            uint32_t head;     //!< first valid codepoint
            uint32_t tail;     //!< last  valid codepoint
            uint8_t  infoMask; //!< Byte1 mask to extract info
            uint8_t  infoBits; //!< Byte1 info once masked
            uint8_t  dataMask; //!< ~infoMask
            unsigned shift[4]; //!< shift to get/put data
            uint32_t dword[4]; //!< mask to get data

            //! (cp >> shift[iByte] | dword[iByte])
            /**
             \param iByte byte index in [0:3]
             \param cp    a code point
             \return extracted data byte
             */
            uint8_t  data(const unsigned iByte, const uint32_t cp) const noexcept;

        };

        static const unsigned   Count = 4;    //!< internal CodePoints
        static const CodePoints Table[Count]; //!< internal CodePoints
        static const uint32_t   MaxCodePoint; //!< last valid code point

        //______________________________________________________________________
        //
        //
        //! Encoding a valid codepoint
        //
        //______________________________________________________________________
        class Encoding
        {
        public:
            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________
            Encoding(const uint32_t);            //!< setup and compute
            ~Encoding() noexcept;                //!< cleanup
            Encoding(const Encoding &) noexcept; //!< duplicate

            //! display, mostly to debug
            friend std::ostream & operator<<(std::ostream &,const Encoding &);

            //__________________________________________________________________
            //
            // Members
            //__________________________________________________________________
            const size_t  size;    //!< encoded size
            const uint8_t byte[4]; //!< encoded bytes

        private:
            Y_Disable_Assign(Encoding); //!< discarding
        };


        //______________________________________________________________________
        //
        //
        //! Decoding by progressive input
        //
        //______________________________________________________________________
        class Decoding
        {
        public:
            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________
            Decoding()  noexcept; //!< initialize to invalid state
            ~Decoding() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            // Methods
            //__________________________________________________________________
            void restart() noexcept;        //!< reset to invalid state
            bool operator()(const uint8_t); //!< update internal state \return true iff decoded
            uint32_t operator*() const;     //!< only when finished \return decoded

            //! restart() and check valid 1 to 4 bytes sequence \return decoded codepoint
            uint32_t operator()(const uint8_t *,size_t);

        private:
            int      missing; //!< missing bytes
            uint32_t decoded; //!< current decoded bits
            unsigned request; //!< initial decoding request

            bool process(const uint8_t); //!< process bulk byte \return true iff decoded
        };


    };

}

#endif

