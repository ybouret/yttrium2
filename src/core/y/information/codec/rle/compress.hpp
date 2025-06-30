
//! \file

#ifndef Y_Information_RLE_Included
#define Y_Information_RLE_Included 1

#include "y/information/codec/q.hpp"

namespace Yttrium
{

    namespace Information
    {
        namespace RLE
        {

            class Compress : public QCodec
            {
            public:
                class Proc;

                explicit Compress();
                virtual ~Compress() noexcept;

                virtual void reset() noexcept;
                virtual void write(const char C);
                virtual void flush();
                
            private:
                Y_Disable_Copy_And_Assign(Compress);
                Proc * const proc;
            };

        }
    }

}


#endif

