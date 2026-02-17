//! \file


#ifndef Y_Concurrent_Divide2D_Included
#define Y_Concurrent_Divide2D_Included 1

#include "y/concurrent/divide/1d.hpp"
#include "y/concurrent/divide/box.hpp"
#include "y/concurrent/divide/hsegment.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        namespace Divide
        {

            //__________________________________________________________________
            //
            //
            //
            //! Specific 1D Tile for 2D computation
            //
            //
            //__________________________________________________________________
            template <typename T>
            class In1D : public Tile1D<T>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const T Zero = 0; //!< alias
                using Tile1D<T>::offset;
                using Tile1D<T>::utmost;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup with zero indexing
                /**
                 \param sz size
                 \param rk rank
                 \param count number of items
                 */
                inline explicit In1D(const size_t   sz,
                                     const size_t   rk,
                                     const T        count) noexcept :
                Tile1D<T>(sz,rk,count,Zero),
                cxxOffset(offset+1),
                cxxUtmost(utmost+1)
                {
                }

                //! cleanup
                inline virtual ~In1D() noexcept {}

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const T cxxOffset; //!< offset+1
                const T cxxUtmost; //!< utmost+1

            private:
                Y_Disable_Copy_And_Assign(In1D); //!< discarding
            };




            //! helper to setup
#define Y_Tile2D_Ctor() \
h(0),                   \
proc(0),                \
head(0),                \
bulk(0),                \
tail(0),                \
wksp()

            //__________________________________________________________________
            //
            //
            //
            //! Tile of horizontal segments
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Tile2D : public In1D<T>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef V2D<T>                    vertex_t; //!< alias
                typedef T                         scalar_t; //!< alias
                typedef Box<vertex_t>             BoxType;  //!< alias
                typedef HSegment<T>               Segment;  //!< alias

                //! method pointer to access a segment
                typedef Segment (Tile2D:: *GetSegment)(const scalar_t) const;

                static const scalar_t  One         = 1;                                      //!< scalar alias
                static const size_t    MaxSegments = 3;                                      //!< head,tail,bulk
                static const size_t    InnerBytes  = MaxSegments * sizeof(Segment);          //!< alias
                static const size_t    InnerWords  = Alignment::WordsGEQ<InnerBytes>::Count; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param sz  sz>0
                 \param rk  rk<sz
                 \param box total area
                 */
                inline explicit Tile2D(const size_t   sz,
                                       const size_t   rk,
                                       const BoxType &box) noexcept :
                In1D<T>(sz,rk,box.count),
                Y_Tile2D_Ctor() {
                    initialize(box);
                }


                //! setup
                /**
                 \param sz  sz>0
                 \param rk  rk<sz
                 */
                inline explicit Tile2D(const size_t   sz,
                                       const size_t   rk) noexcept :
                In1D<T>(sz,rk,In1D<T>::Zero),
                Y_Tile2D_Ctor() {
                    assert( this->isEmpty() );
                    (void) base();
                }


                //! cleanup
                inline virtual ~Tile2D() noexcept { }

                //! display
                inline friend std::ostream & operator<<(std::ostream &os, const Tile2D &t)
                {
                    if(t.h<=0)
                        os << Subdivision::Empty;
                    else
                        os << "|" << t.origin() << "->" << t.finish() << "|=" << t.length << "/#" << t.h;
                    return os;
                }
                

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! \return finish coordinate
                inline vertex_t finish() const noexcept {
                    assert(h>0); return tail->right();
                }

                //! \return origin coordinate
                inline vertex_t origin() const noexcept {
                    assert(h>0); return head->start;
                }


                //! \param j 1<=j<=h \return matching segment
                inline const Segment operator[](const scalar_t j) const noexcept
                {
                    assert(j>0); assert(j<=h);
                    return (*this.*proc)(j);
                }


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const scalar_t h; //!< height
                
            private:
                Y_Disable_Copy_And_Assign(Tile2D);        //!< discarding
                GetSegment const      proc;               //!< access function depending on h
                const Segment * const head;               //!< first segment
                const Segment * const bulk;               //!< bulk/helper segment
                const Segment * const tail;               //!< last segment
                void *                wksp[ InnerWords ]; //!< memory for segments

                //! \return inner memory
                inline Segment * base() noexcept
                {
                    return static_cast<Segment *>( Y_Memory_BZero(wksp) );
                }


                //! initialize part of the box \param box box to map
                inline void initialize(const BoxType &box) noexcept
                {

                    //----------------------------------------------------------
                    // consider 1D indices
                    //----------------------------------------------------------
                    const Tile1D<scalar_t> & tile1d = *this;
                    if( tile1d.isEmpty() ) {
                        assert(0==h);
                        assert(!proc);
                        return;
                    }

                    //----------------------------------------------------------
                    // convert to vertices
                    //----------------------------------------------------------
                    const vertex_t  ini = box.at(tile1d.offset);
                    const vertex_t  end = box.at(tile1d.utmost);
                    const Subdivision &ctx = *this;
                    std::cerr << "@" << ctx << ": cut from  " << ini << " to " << end << " : h=" << (One + end.y - ini.y) << std::endl;
                    switch(  Coerce(h) = One + end.y - ini.y )
                    {
                        case 1:  set1(ini,end);     break;
                        case 2:  set2(ini,end,box); break;
                        default: setH(ini,end,box); break;
                    }
                }


                //! set for h=1 \param ini ini \param end end
                inline void set1(const vertex_t &ini, const vertex_t &end) noexcept
                {
                    assert(1==h);
                    //----------------------------------------------------------
                    //
                    // same head and tail, no bulk
                    //
                    //----------------------------------------------------------
                    Segment * const seg = base();
                    Coerce(head) = Coerce(tail) = seg;
                    Coerce(proc) = & Tile2D:: Get1;
                    const vertex_t start = ini;
                    const scalar_t width = One + end.x - ini.x;
                    new (seg) Segment(start,width);
                }


                //! set for h=2 \param ini ini \param end end \param box box
                inline void set2(const vertex_t &ini, const vertex_t &end, const BoxType &box) noexcept
                {
                    assert(2==h);
                    //----------------------------------------------------------
                    //
                    // head and tail, bulk set to head-1 for access h=1,2
                    //
                    //----------------------------------------------------------
                    Segment * const seg = base();
                    Coerce(head) = seg;
                    Coerce(tail) = head+1;
                    Coerce(bulk) = head-1;
                    Coerce(proc) = & Tile2D:: Get2;

                    {   // first segment
                        const vertex_t start = ini;
                        const scalar_t width = One + box.upper.x - ini.x;
                        new (seg+0) Segment(start,width);
                    }

                    {   // second segment
                        const vertex_t start(box.lower.x,end.y);
                        const scalar_t width = One + end.x - box.lower.x;
                        new (seg+1) Segment(start,width);
                    }
                }

                //! set for h>=3 \param ini ini \param end end \param box box
                inline void setH(const vertex_t &ini, const vertex_t &end, const BoxType &box) noexcept
                {
                    assert(h>=3);

                    //----------------------------------------------------------
                    //
                    // head and tail, bulk set to head-1 for access h=1,2
                    //
                    //----------------------------------------------------------
                    Segment * const seg = base();
                    Coerce(proc) = & Tile2D:: GetH;

                    //--------------------------------------------------
                    // fist segment
                    //--------------------------------------------------
                    {
                        const vertex_t start = ini;
                        const scalar_t width = One + box.upper.x - ini.x;
                        Coerce(head) = seg;
                        new (seg+0) Segment(start,width);
                    }

                    //--------------------------------------------------
                    // last segment
                    //--------------------------------------------------
                    {
                        const vertex_t start(box.lower.x,end.y);
                        const scalar_t width = One + end.x - box.lower.x;
                        Coerce(tail) = seg;
                        new (seg+1) Segment(start,width);
                    }

                    //--------------------------------------------------
                    // bulk, call from j=2 => subtract one
                    //--------------------------------------------------
                    {
                        const vertex_t start(box.lower.x,ini.y-One);
                        const scalar_t width = box.width.x;
                        Coerce(bulk) = seg;
                        new (seg+2) Segment(start,width);
                    }
                }


                //! \return head=tail segment, h=1
                inline Segment Get1(const scalar_t) const noexcept
                {
                    assert(1==h);
                    assert(0==bulk);
                    assert(head==tail);
                    return *head;
                }

                //! \param j 1<=j<=2 \return bulk[1..2], precomputed
                inline Segment Get2(const scalar_t j) const noexcept
                {
                    assert(2==h);
                    assert(j>=1); assert(j<=2);
                    assert(head);
                    assert(tail);
                    assert(bulk);
                    assert(head+1==tail);
                    assert(head-1==bulk);
                    return bulk[j];
                }

                //! \param j 1<=j<=h \return j=1:head; j=h:tail; bulk shifted by j
                inline Segment GetH(const scalar_t j) const noexcept
                {
                    assert(h>=3);
                    assert(j>=1); assert(j<=h);
                    assert(head);
                    assert(tail);
                    assert(bulk);
                    if(j<=1) return *head;
                    if(j<h) {
                        Segment s = *bulk;
                        Coerce(s.start.y) += j;
                        return s;
                    }
                    return *tail;
                }

            };


            //__________________________________________________________________
            //
            //
            //
            //! Tile2D partition
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Tiles2D :
            public Writable< Tile2D<T> >,
            public Leap< V2D<T> >
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Tile2D<T>              Tile;      //!< alias
                typedef typename Tile::BoxType BoxType;   //!< alias
                typedef const BoxType &        Parameter; //!< alias
                typedef Writable<Tile2D<T>>    BaseType;  //!< alias


                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param n   partition size
                 \param box total area
                 */
                inline explicit Tiles2D(const size_t   n,
                                        const BoxType  box) :
                BaseType(),
                Leap<V2D<T>>(box),
                tiles(n)
                {
                    buildTiles(n,box);
                }

                //! setup empty, with abnormal leap
                /**
                 \param n   partition size
                 */
                inline explicit Tiles2D(const size_t n) :
                BaseType(),
                Leap<V2D<T>>( V2D<T>(1,1), V2D<T>(0,0) ),
                tiles(n)
                {
                    for(size_t i=0;i<n;++i) tiles.push(n,i);
                }

                //! cleanup
                inline virtual ~Tiles2D() noexcept {}

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                inline virtual size_t size() const noexcept { return tiles.size(); }

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! \return readable interface
                inline const Readable< Tile2D<T> > & content() const noexcept
                {
                    return *this;
                }

                //! remap if necessary \param box new bounding box \return true if changed
                inline bool remap(const BoxType &box)
                {
                    // check same bounding box
                    {
                        const Leap< V2D<T> > &rhs = *this;
                        if( box == rhs ) return false;
                    }

                    // free/build and update leap
                    {
                        { const size_t n = tiles.size(); tiles.free(); buildTiles(n,box); }
                        Coerce(this->lower) = box.lower;
                        Coerce(this->upper) = box.upper;
                    }

                    return true;
                }


            private:
                Y_Disable_Copy_And_Assign(Tiles2D); //!< discarding
                CxxSeries<Tile> tiles; //!< computed tiles

                //! \param n number of tiles \param box (new) box
                inline void buildTiles(const size_t n, const BoxType &box) noexcept
                {
                    assert( 0 == tiles.size() );
                    for(size_t i=0;i<n;++i) tiles.push(n,i,box);
                }

                inline virtual const Tile & getItemAt(const size_t indx) const noexcept
                {
                    return tiles[indx];
                }
            };
        }

    }

}

#endif // !Y_Concurrent_Divide2D_Included

