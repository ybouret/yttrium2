//! \file


#ifndef Y_Concurrent_Divide2D_Included
#define Y_Concurrent_Divide2D_Included 1

#include "y/concurrent/divide/1d.hpp"
#include "y/concurrent/divide/box.hpp"
#include "y/concurrent/divide/hsegment.hpp"
#include "y/object/school-of.hpp"
#include "y/pointer/arc.hpp"

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
                static  const T Zero = 0; //!< alias

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
                cxxOffset(this->offset+1),
                cxxUtmost(this->utmost+1)
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




            //! helper
#define Y_Tile2D_Ctor() \
h(0),\
segments( new SegsMem(1) ),\
proc(0),\
head(0), bulk(0), tail(0), \
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
                typedef HSegment<T>               SegType;  //!< alias
                typedef Memory::SchoolOf<SegType> SegsMem;  //!< alias
                typedef ArcPtr<SegsMem>           Segments; //!< alias

                typedef HSegment<T> Segment;
                typedef Segment (Tile2D:: *GetSegment)(const scalar_t) const;
                static const size_t MaxSegments = 3;
                static const size_t InnerBytes  = MaxSegments * sizeof(Segment);
                static const size_t InnerWords  = Alignment::WordsGEQ<InnerBytes>::Count;

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
                                       const BoxType &box) :
                In1D<T>(sz,rk,box.count),
                Y_Tile2D_Ctor() {
                    setup(box);
                    initialize(box);
                    if( this->isEmpty() ) return;
                    assert(h>0);
                    assert(proc);
                    bool bad = false;
                    for(scalar_t j=1;j<=h;++j)
                    {
                        const Segment lhs = segments->cxx[j];
                        const Segment rhs = (*this.*proc)(j);
                        if( lhs!=rhs )
                        {
                            bad = true;
                            std::cerr << "bad segments " << j << "/" << h << " old=" << lhs << " | new=" << rhs << std::endl;
                        }
                    }
                    std::cerr << ( bad ? "bad" : "ok" ) << " " << *this << std::endl;
                    if(bad) exit(0);
                }


                //! setup
                /**
                 \param sz  sz>0
                 \param rk  rk<sz
                 */
                inline explicit Tile2D(const size_t   sz,
                                       const size_t   rk) :
                In1D<T>(sz,rk,In1D<T>::Zero),
                Y_Tile2D_Ctor() {
                    assert( this->isEmpty() );
                    (void) base();
                }


                //! cleanup
                inline virtual ~Tile2D() noexcept {
                }

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
                // Method
                //
                //______________________________________________________________

                //! \return finish coordinate
                inline vertex_t finish() const noexcept
                {
                    assert(h>0); return tail->right();
                    //return (h>0) ? segments->cxx[h].right() : vertex_t();
                }

                //! \return origin coordinate
                inline vertex_t origin() const noexcept
                {
                    assert(h>0); return head->start;
                    //return (h>0) ? segments->entry[0].start : vertex_t();
                }


                //! \param j 1<=j<=h \return matching segment
                inline const SegType operator[](const scalar_t j) const noexcept
                {
                    assert(j>0); assert(j<=h);
                    return segments->cxx[j];
                }


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const scalar_t h; //!< height
                
            private:
                Y_Disable_Copy_And_Assign(Tile2D); //!< discarding
                Segments   segments;               //!< memory for segments
                GetSegment const      proc;        //!< access function depending on h
                const Segment * const head;        //!< first segment
                const Segment * const bulk;        //!< bulk/helper segment
                const Segment * const tail;        //!< last segment
                void *     wksp[ InnerWords ];     //!< memory for segments

                //! \return inner memory
                inline Segment * base() noexcept
                {
                    return static_cast<Segment *>( Y_Memory_BZero(wksp) );
                }

                //! \return head=tail segment, h=1
                inline Segment Get1(const scalar_t) const noexcept
                {
                    assert(1==h);
                    assert(0==bulk);
                    assert(head==tail);
                    return *head;
                }

                //! \return bulk[1..2], precomputed
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



                inline void initialize(const BoxType &box) noexcept
                {
                    static const scalar_t  one = 1;

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
                    Segment *       seg = base();
                    Coerce(h) = one + end.y - ini.y; assert(h>0);


                    switch(h)
                    {
                            //--------------------------------------------------
                            //
                            // same head and tail, no bulk
                            //
                            //--------------------------------------------------
                        case 1: {
                            Coerce(head) = Coerce(tail) = seg;
                            Coerce(proc) = & Tile2D:: Get1;
                            const vertex_t start = ini;
                            const scalar_t width = one + end.x - ini.x;
                            new (seg) Segment(start,width);
                        } return;

                            //--------------------------------------------------
                            //
                            // head and tail, bulk set to head-1 for access h=1,2
                            //
                            //--------------------------------------------------
                        case 2: {
                            Coerce(head) = seg;
                            Coerce(tail) = head+1;
                            Coerce(bulk) = head-1;
                            Coerce(proc) = & Tile2D:: Get2;

                            {   // first segment
                                const vertex_t start = ini;
                                const scalar_t width = one + box.upper.x - ini.x;
                                new (seg++) Segment(start,width);
                            }

                            {   // second segment
                                const vertex_t start(box.lower.x,end.y);
                                const scalar_t width = one + end.x - box.lower.x;
                                new (seg) Segment(start,width);
                            }


                        } return;

                            //--------------------------------------------------
                            //
                            // head, tail, and first bulk
                            //
                            //--------------------------------------------------
                        default:
                        {
                            assert(h>=3);
                            Coerce(proc) = & Tile2D:: GetH;

                            // fist segment
                            {
                                const vertex_t start = ini;
                                const scalar_t width = one + box.upper.x - ini.x;
                                Coerce(head) = seg;
                                new (seg++) Segment(start,width);
                            }

                            // last segment
                            {
                                const vertex_t start(box.lower.x,end.y);
                                const scalar_t width = one + end.x - box.lower.x;
                                Coerce(tail) = seg;
                                new (seg++) Segment(start,width);
                            }

                            // bulk
                            {
                                const vertex_t start(box.lower.x,ini.y);
                                const scalar_t width = box.width.x;
                                Coerce(bulk) = seg;
                                new (seg) Segment(start,width);
                            }
                        } return;
                    }
                }


                //! setup algorithm
                /**
                 \param box  total working box
                 */
                inline void setup(const BoxType &box)
                {
                    static const scalar_t  one = 1;

                    //----------------------------------------------------------
                    // find indices
                    //----------------------------------------------------------
                    const Tile1D<scalar_t> & tile1d = *this;
                    if( tile1d.isEmpty() ) return;


                    //----------------------------------------------------------
                    // convert to vertices
                    //----------------------------------------------------------
                    const vertex_t ini = box.at(tile1d.offset);
                    const vertex_t end = box.at(tile1d.utmost);

                    //----------------------------------------------------------
                    // compute and allocate number of segments
                    //----------------------------------------------------------
                    {
                        const scalar_t required = end.y-ini.y+one;
                        const size_t   nhs      = (size_t)required;
                        if(nhs>segments->maxBlocks)
                        {
                            Segments tmp( new SegsMem(nhs) );
                            segments.xch(tmp);
                        }
                        Coerce(h) = required;
                    }

                    //----------------------------------------------------------
                    // convert to horizontal segments
                    //----------------------------------------------------------
                    const scalar_t htop = h-one;
                    for(scalar_t y=0;y<h;++y)
                    {
                        // lhs/rhs vertices from box
                        vertex_t lhs(box.lower.x,ini.y+y);
                        vertex_t rhs(box.upper.x,lhs.y);

                        // cut if necessary
                        if(y<=0)    lhs.x = ini.x;
                        if(y>=htop) rhs.x = end.x;
                        assert(lhs.y==rhs.y);
                        assert(rhs.x>=lhs.x);
                        const scalar_t w = one+rhs.x-lhs.x;

                        // record
                        new (segments->entry+y) SegType(lhs,w);
                        //Coerce(n) += (uint64_t)w;
                    }
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
                    for(size_t i=0;i<n;++i) tiles.push(n,i,box);
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

                    // create/exchange
                    {
                        Tiles2D t(tiles.size(),box);
                        tiles.xch(t.tiles);
                        Coerce(this->lower) = box.lower;
                        Coerce(this->upper) = box.upper;
                    }

                    return true;
                }


            private:
                Y_Disable_Copy_And_Assign(Tiles2D); //!< discarding
                CxxSeries<Tile> tiles; //!< computed tiles

                inline virtual const Tile & getItemAt(const size_t indx) const noexcept
                {
                    return tiles[indx];
                }
            };
        }

    }

}

#endif // !Y_Concurrent_Divide2D_Included

