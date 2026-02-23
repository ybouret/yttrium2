
//! \file

#ifndef Y_Ink_Gradient_Included
#define Y_Ink_Gradient_Included 1

#include "y/ink/pixmap.hpp"

namespace Yttrium
{
    namespace Ink
    {
        template <typename T>
        class Gradient : public Pixmap<T>
        {
        public:
            typedef V2D<T> vtx_t;

            inline explicit Gradient(const size_t w, const size_t h) :
            Pixmap<T>(w,h), dir(w,h)
            {
            }
            


            Pixmap<vtx_t>  dir;
        private:
            Y_Disable_Copy_And_Assign(Gradient);
        };
    }

}

#endif // !Y_Ink_Gradient_Included
