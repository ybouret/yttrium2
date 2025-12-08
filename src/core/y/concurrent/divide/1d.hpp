//! \file


#ifndef Y_Concurrent_Divide1D_Included
#define Y_Concurrent_Divide1D_Included 1

#include "y/concurrent/member.hpp"
#include "y/type/args.hpp"
#include "y/container/cxx/series.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        namespace Divide
        {

#define Y_Concurrent_Divide_Tile1D_Utmost (offset + length - One)

#define Y_Concurrent_Divide_Tile1D(CTOR) \
offset(iFirst), \
length( CTOR ), \
utmost( Y_Concurrent_Divide_Tile1D_Utmost )

            template <typename T>
            class Tile1D
            {
            public:
                static const T One = 1;
                Y_Args_Expose(T,Type);

                inline Tile1D(const size_t  mySize,
                              const size_t  myIndx,
                              ConstType     extent,
                              ConstType     iFirst) noexcept :
                Y_Concurrent_Divide_Tile1D( Member::Part(mySize,myIndx, extent, Coerce(offset) ) )
                {

                }

                inline Tile1D(const Member & member,
                              ConstType      extent,
                              ConstType      iFirst) noexcept :
                Y_Concurrent_Divide_Tile1D( member.part( extent, Coerce(offset) ) )
                {

                }


                inline Tile1D(const Tile1D &s) noexcept :
                offset(s.offset),
                length(s.length),
                utmost(s.utmost)
                {
                }

                inline virtual ~Tile1D() noexcept
                {

                }

                inline friend std::ostream & operator<<(std::ostream &os, const Tile1D &t)
                {
                    if(t.length<=0)
                        return os << "|empty|";
                    else
                        return os << "|[" << t.offset << ":" << t.utmost << "]|=" << t.length;
                }


                inline friend bool operator==(const Tile1D &lhs, const Tile1D &rhs) noexcept
                {
                    return lhs.offset == rhs.offset && lhs.length == rhs.length;
                }

              ConstType offset; //!< user's offset
              ConstType length; //!< 0 : empty
              ConstType utmost; //!< utmost = offset + length - 1

            private:
                Y_Disable_Assign(Tile1D);
            };


            template <typename T>
            class Tiles1D : public Readable< Tile1D<T> >
            {
            public:
                Y_Args_Expose(T,Type);
                typedef Tile1D<T> Tile;
                typedef ConstType Parameter;

                inline explicit Tiles1D(const size_t n,
                                        ConstType    extent,
                                        ConstType    iFirst) :
                tiles(n)
                {
                    for(size_t i=1;i<=n;++i)
                        tiles.push(n,i,extent,iFirst);
                }

                inline virtual ~Tiles1D() {}

                inline Tiles1D(const Tiles1D &t) : tiles(t) { }



                inline virtual size_t size() const noexcept { return tiles.size(); }
                


            private:
                Y_Disable_Assign(Tiles1D);
                CxxSeries<const Tile> tiles;
                inline virtual const Tile & getItemAt(const size_t indx) const noexcept
                {
                    return tiles[indx];
                }
            };

            template <typename T>
            class CxxTiles1D : public Tiles1D<T>
            {
            public:
                Y_Args_Expose(T,Type);
                static ConstType Offset1 = 1;

                inline explicit CxxTiles1D(const size_t n,
                                           ConstType    extent) :
                Tiles1D<T>(n,extent,Offset1)
                {
                }

                inline virtual ~CxxTiles1D() noexcept
                {
                }

            private:
                Y_Disable_Copy_And_Assign(CxxTiles1D);
            };


            




        }
    }

}

#endif // !Y_Concurrent_Divide1D_Included

