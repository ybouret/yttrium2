
//! \file

#ifndef Y_Ink_Histogram_Included
#define Y_Ink_Histogram_Included 1

#include "y/ink/ops.hpp"
#include "y/memory/stealth.hpp"
#include "y/string/fwd.hpp"

namespace Yttrium
{
    namespace Ink
    {
        //______________________________________________________________________
        //
        //
        //
        //! Histogram of pixels
        //
        //
        //______________________________________________________________________
        class Histogram
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef uint32_t    Type;                               //!< alias
            static const size_t Bins = 256;                         //!< number of bins
            static const size_t LocalMemory = Bins * sizeof(Type); //!< local memory

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Histogram() noexcept; //!< setup
            virtual ~Histogram() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Histogram & ldz()                            noexcept; //!< \return cleared histogram
            Type &       operator[](const uint8_t)       noexcept; //!< \return access
            const Type & operator[](const uint8_t) const noexcept; //!< \return const access

            Histogram & operator+= (const Type * const) noexcept; //!< \return cumulative histogram
            Histogram & operator+= (const Histogram &)  noexcept; //!< \return cumulative histogram

            //! \return bin-wise equality
            friend bool operator==(const Histogram &, const Histogram &) noexcept;

            //! process all pixmap
            /**
             \param broker par/seq broker
             \param pxm pixmap
             \param proc convert each pixel to yte
             */
            template <typename PIXMAP, typename PIXEL_TO_BYTE> inline
            void add(Broker &broker, const PIXMAP &pxm, PIXEL_TO_BYTE &proc)
            {
                broker.acquireLocalMemory( LocalMemory );
                broker.run(CallAdd<PIXMAP,PIXEL_TO_BYTE>,pxm,proc);
            }

            //! \param lo lower bin \param upper bin \return median bin
            uint8_t median(const uint8_t lo, const uint8_t up) const noexcept;

            void save(const Core::String<char> &) const; //!< save histogram data
            void save(const char * const)         const; //!< save histogram data


        private:
            Y_Disable_Copy_And_Assign(Histogram); //!< discarding
            Type bin[Bins];                       //!< current data

            //! process pixmap per tile
            /**
             \param tile tile to process
             \param pxm  pixmap to process
             \param proc convert pixel to byte
             */
            template <typename PIXMAP, typename PIXEL_TO_BYTE> static
            inline void CallAdd(Lockable      &,
                                const Tile    & tile,
                                const PIXMAP  & pxm,
                                PIXEL_TO_BYTE & proc)
            {
                assert( tile.entry );
                assert( tile.bytes >= LocalMemory );
                assert( Memory::Stealth::Are0(tile.entry,tile.bytes) );
                Type * const h = static_cast<Type *>(tile.entry);
                for(unit_t k=tile.h;k>0;--k)
                {
                    const Segment               s = tile[k];
                    const typename PIXMAP::Row &r = pxm[s.start.y];
                    for(unit_t n=s.width,x=s.start.x;n>0;--n,++x)
                        ++h[(uint8_t)proc(r[x])];
                }
            }
        };
    }

}

#endif // !Y_Ink_Histogram_Included
