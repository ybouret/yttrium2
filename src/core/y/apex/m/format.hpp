

//! \file

#ifndef Y_Apex_Format_Included
#define Y_Apex_Format_Included 1

#include "y/apex/m/size-for.hpp"
#include <cassert>

namespace Yttrium
{

    namespace Apex
    {


        template <typename U> struct UFormat;


        //! UFormat<uint64_t>
        template <> struct UFormat<uint64_t>
        {
            //! \param data input \return &data
            static inline
            const uint64_t * Make(uint64_t &data, const size_t) noexcept
            {
                return &data;
            };
        };

        //! UFormat<uint32_t>
        template <> struct UFormat<uint32_t>
        {
            //! \param data input \param size dwords \return big-endian 32-bits data
            static inline
            uint32_t * Make(uint64_t &data, const size_t size) noexcept
            {
                assert(size<=2);
                uint64_t          v = data;
                uint32_t * const  u = (uint32_t *) &data;
                switch(size)
                {
                    case 2: u[1] = uint32_t(v>>32); // FALLTHRU
                    case 1: u[0] = uint32_t(v);
                        break;
                    default:
                        assert(0==size);
                        break;
                }
                return u;
            };
        };

        //! UFormat<uint16_t>
        template <> struct UFormat<uint16_t>
        {
            //! \param data input \param size words \return big-endian 16-bits data
            static inline
            uint16_t * Make(uint64_t &data, const size_t size) noexcept
            {
                assert(size<=4);
                uint64_t          v = data;
                uint16_t * const  u = (uint16_t *) &data;
                switch(size)
                {
                    case 4: u[3] = uint16_t(v>>48); // FALLTHRU
                    case 3: u[2] = uint16_t(v>>32); // FALLTHRU
                    case 2: u[1] = uint16_t(v>>16); // FALLTHRU
                    case 1: u[0] = uint16_t(v);
                        break;
                    default:
                        assert(0==size);
                        break;
                }
                return u;
            };
        };

        //! UFormat<uint8_t>
        template <> struct UFormat<uint8_t>
        {
            //! \param data input \param size bytes \return big-endian 8-bits data
            static inline
            uint8_t * Make(uint64_t &data, const size_t size) noexcept
            {
                assert(size<=4);
                uint64_t         v = data;
                uint8_t * const  u = (uint8_t *) &data;
                switch(size)
                {
                    case 8: u[7] = uint8_t(v>>56); // FALLTHRU
                    case 7: u[6] = uint8_t(v>>48); // FALLTHRU
                    case 6: u[5] = uint8_t(v>>40); // FALLTHRU
                    case 5: u[4] = uint8_t(v>>32); // FALLTHRU
                    case 4: u[3] = uint8_t(v>>24); // FALLTHRU
                    case 3: u[2] = uint8_t(v>>16); // FALLTHRU
                    case 2: u[1] = uint8_t(v>>8);  // FALLTHRU
                    case 1: u[0] = uint8_t(v);
                        break;
                    default:
                        assert(0==size);
                        break;
                }
                return u;
            };
        };

        
        //! transform natural_t into T[]
        /**
         \param data original value, final workspace
         \param size computed according to data bits
         \return workspace ready for Model ops
         */
        template <typename T> inline
        const T * UFormatAs(natural_t &data, size_t &size)
        {
            size = SizeFor<T>::From( Calculus::BitsFor::Count(data) );
            return UFormat<T>::Make(data,size);
        }
    }

}

#endif

