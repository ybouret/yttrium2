//! \file


#ifndef Y_Concurrent_Divide1D_Included
#define Y_Concurrent_Divide1D_Included 1

#include "y/concurrent/member.hpp"
#include "y/type/args.hpp"
#include "y/container/cxx/series.hpp"
#include "y/concurrent/divide/subdivision.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        namespace Divide
        {

            //! helper
#define Y_Concurrent_Divide_Tile1D_Utmost (ConstType)(offset + length - One)

            //! helper
#define Y_Concurrent_Divide_Tile1D(CTOR) \
offset(iFirst), \
length( CTOR ), \
utmost( Y_Concurrent_Divide_Tile1D_Utmost )

            //__________________________________________________________________
            //
            //
            //
            //! Tile in 1D
            //
            //
            //__________________________________________________________________'
            template <typename T>
            class Tile1D : public Subdivision
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                Y_Args_Expose(T,Type);    //!< alias
                static ConstType One = 1; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________'

                //! setup from coordinates
                /**
                 \param mySize mySize > 0
                 \param myIndx 1 <= myIndx <= mySize
                 \param extent total burden
                 \param iFirst first index
                 */
                inline Tile1D(const size_t  mySize,
                              const size_t  myIndx,
                              ConstType     extent,
                              ConstType     iFirst) noexcept :
                Y_Concurrent_Divide_Tile1D( Member::Part<MutableType>(mySize,myIndx, extent, Coerce(offset) ) )
                {

                }

                //! setup from Member
                /**
                 \param member given member
                 \param extent total burden
                 \param iFirst first index
                 */
                inline Tile1D(const Member & member,
                              ConstType      extent,
                              ConstType      iFirst) noexcept :
                Y_Concurrent_Divide_Tile1D( member.part<MutableType>( extent, Coerce(offset) ) )
                {

                }

                //! duplicate \param t another tile
                inline Tile1D(const Tile1D &t) noexcept :
                offset(t.offset),
                length(t.length),
                utmost(t.utmost)
                {
                }

                //! cleanup
                inline virtual ~Tile1D() noexcept {}


                //! display
                inline friend std::ostream & operator<<(std::ostream &os, const Tile1D &t)
                {
                    if(t.length<=0)
                        return os << Empty;
                    else
                        return os << "|[" << t.offset << ":" << t.utmost << "]|=" << t.length;
                }

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________'

                //! \param lhs first tile \param rhs second tile \return equality
                inline friend bool operator==(const Tile1D &lhs, const Tile1D &rhs) noexcept
                {
                    return lhs.offset == rhs.offset && lhs.length == rhs.length;
                }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________'
                ConstType offset; //!< user's offset
                ConstType length; //!< 0 : empty
                ConstType utmost; //!< utmost = offset + length - 1

            private:
                Y_Disable_Assign(Tile1D); //!< discarding
            };



            //__________________________________________________________________
            //
            //
            //
            //! Tile1D partition
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Tiles1D : public Readable< Tile1D<T> >
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                Y_Args_Expose(T,Type);               //!< alias
                typedef Tile1D<T>      Tile;         //!< alias
                typedef ConstType      Parameter;    //!< alias
                typedef Readable<Tile> ReadableType; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param n      partition size
                 \param extent total burden
                 \param iFirst first index
                 */
                inline explicit Tiles1D(const size_t n,
                                        ConstType    extent,
                                        ConstType    iFirst) :
                ReadableType(),
                tiles(n)
                {
                    for(size_t i=1;i<=n;++i)
                        tiles.push(n,i,extent,iFirst);
                }

                //! cleanup
                inline virtual ~Tiles1D() {}

                //! duplicate \param t another tile
                inline Tiles1D(const Tiles1D &t) : ReadableType(), tiles(t) { }

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________'
                inline virtual size_t size() const noexcept { return tiles.size(); }



            private:
                Y_Disable_Assign(Tiles1D);   //!< dicarding
                CxxSeries<const Tile> tiles; //!< built tiles

                inline virtual const Tile & getItemAt(const size_t indx) const noexcept
                {
                    return tiles[indx];
                }
            };

            //__________________________________________________________________
            //
            //
            //
            //! Tiles1D with first index=1
            //
            //
            //__________________________________________________________________
            template <typename T>
            class CxxTiles1D : public Tiles1D<T>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________'
                Y_Args_Expose(T,Type);         //!< alias
                static ConstType Offset1 = 1;  //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________'

                //! setup \param n parition size \param extent total burden
                inline explicit CxxTiles1D(const size_t n,
                                           ConstType    extent) :
                Tiles1D<T>(n,extent,Offset1)
                {
                }

                //! cleanup
                inline virtual ~CxxTiles1D() noexcept
                {
                }

            private:
                Y_Disable_Copy_And_Assign(CxxTiles1D); //!< discardind
            };







        }
    }

}

#endif // !Y_Concurrent_Divide1D_Included

