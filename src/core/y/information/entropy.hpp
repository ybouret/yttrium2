
//! \file

#ifndef Y_Information_Entropy_Included
#define Y_Information_Entropy_Included 1

#include "y/stream/output.hpp"

namespace Yttrium
{

    namespace Information
    {

        //______________________________________________________________________
        //
        //
        //
        //! Entropy computation
        //
        //
        //______________________________________________________________________
        class Entropy : public OutputStream
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Entropy() noexcept;                    //!< setup
            virtual ~Entropy() noexcept;           //!< cleanup
            Entropy(const Entropy &) noexcept;     //!< duplicate
            Entropy & operator=(const Entropy &);  //!< assign \return *this

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void write(const char C);
            virtual void flush();
            
            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void        ldz() noexcept; //!< reset
            long double operator()(void) const noexcept; //!< \return current entropy

        private:
            uint64_t bin[256]; //!< count of each byte
        };
    }

}


#endif
