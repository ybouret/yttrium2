
//! \file

#ifndef Y_Ink_Blobs_Included
#define Y_Ink_Blobs_Included 1


#include "y/ink/pixmap.hpp"
#include "y/ink/broker.hpp"
#include "y/container/sequence/vector.hpp"

namespace Yttrium
{
    namespace Ink
    {
        typedef Pixmap<size_t> IndexMap;

        class Blobs : public IndexMap
        {
        public:
            static const Type   Zero = 0;
            static const unit_t Delta[8][2];


            explicit Blobs(const size_t W, const size_t H);
            virtual ~Blobs() noexcept;


            void build(Broker          & broker,
                       Pixmap<uint8_t> & edge);

            Vector<Point> stack;


        private:
            Y_Disable_Copy_And_Assign(Blobs);
        };

      
    }

}

#endif // !Y_Ink_Blobs_Included

