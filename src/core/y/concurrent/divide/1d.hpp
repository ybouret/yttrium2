//! \file


#ifndef Y_Concurrent_Divide1D_Included
#define Y_Concurrent_Divide1D_Included 1

#include "y/concurrent/member.hpp"
#include "y/type/args.hpp"

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
        }
    }

}

#endif // !Y_Concurrent_Divide1D_Included

