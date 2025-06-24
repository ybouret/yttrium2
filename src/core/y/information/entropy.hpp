
//! \file

#ifndef Y_Information_Entropy_Included
#define Y_Information_Entropy_Included 1

#include "y/stream/output.hpp"

namespace Yttrium
{

    namespace Information
    {

        class Entropy : public OutputStream
        {
        public:
            Entropy() noexcept;
            virtual ~Entropy() noexcept;
            Entropy(const Entropy &) noexcept;
            Entropy & operator=(const Entropy &);

            virtual void write(const char C);
            virtual void flush();
            virtual void frame(const void * const, const size_t);
            
            void ldz() noexcept;
            long double operator()(void) const;

        private:
            uint64_t bin[256];
        };
    }

}


#endif
