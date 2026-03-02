
#include "y/ink/edge/blobs.hpp"
#include "y/ink/ops/ld.hpp"

namespace Yttrium
{
    namespace Ink
    {
        const unit_t Blobs:: Delta[8][2] =
        {
            // axis
            {  1,  0 },
            {  0,  1 },
            { -1,  0 },
            {  0, -1 },
            // diag
            {  1,  1 },
            { -1,  1 },
            { -1, -1 },
            {  1, -1 }
        };

        Blobs:: Blobs(const size_t W, const size_t H) :
        IndexMap(W,H)
        {
        }

        Blobs:: ~Blobs() noexcept
        {
        }

        void Blobs:: build(Broker          & broker,
                           Pixmap<uint8_t> & edge)
        {
            static const Point * const delta = Memory::Stealth::Cast<Point>( &Delta[0][0] );
            const size_t ncof = 8;
            IndexMap &   self = *this;
            assert(Ops::HaveSameArea(self,edge));

            // initialize map
            LoadPixel::Set(broker,*this,Zero);
            size_t indx = 0;

            // walk all the source
            for(unit_t y=lower.y;y<=upper.y;++y)
            {
                const Pixmap<uint8_t>::Row & erow = edge[y];
                IndexMap::Row              & irow = (*this)[y];
                for(unit_t x=lower.x;x<=upper.x;++x)
                {
                    const uint8_t eval = erow[x];
                    if(eval<=0)   continue; // no edge
                    if(irow[x]>0) continue; // already detected

                    // start new blob with new index
                    ++indx; stack.free();
                    stack << Point(x,y);
                    while( stack.size() > 0 )
                    {
                        const Point p = stack.pullTail();
                        if(0!=self[p]) { assert(indx==self[p]); continue; }
                        self[p] = indx;
                        for(size_t i=0;i<ncof;++i)
                        {
                            const Point q = p + delta[i];
                            if(!self.contains(q)) continue;
                            if(0==edge[q])        continue;
                            if(0!=self[q])        continue;
                            stack << q;
                        }
                    }
                }
            }

            std::cerr << "indx=" << indx << std::endl;

        }
    }

}
