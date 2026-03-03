
//! \file

#ifndef Y_Ink_Image_Points_Included
#define Y_Ink_Image_Points_Included 1

#include "y/ink/area.hpp"
#include "y/protean/coop/heavy/list.hpp"
#include "y/threading/multi-threaded-handle.hpp"

namespace Yttrium
{
    namespace Ink
    {

        typedef Protean::CoopHeavyList<Point,MultiThreadedHandle> PointListType;
        typedef PointListType::PoolType                           PointPoolType;
        typedef PointListType::NodeType                           PointNode;

        class PointList : public PointListType
        {
        public:
            explicit PointList();
            virtual ~PointList();
            //PointList(const PointList &);

        private:
            Y_Disable_Assign(PointList);
        };

    }

}

#endif // !Y_Ink_Image_Points_Included
