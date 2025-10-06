
#ifndef Y_Container_Iter_Tests_Included
#define Y_Container_Iter_Tests_Included 1

#include "y/system/compiler.hpp"
#include <iostream>
#include <iomanip>

namespace Yttrium
{
    namespace Iter
    {
        //! Tests for Iterator(s)
        struct Test
        {

            //! show all content \param curr first valid \param last first invalid
            template <typename ITERATOR> static inline
            void Run(ITERATOR curr, const ITERATOR last)
            {
                for(size_t i=1;curr!=last;++curr,++i)
                {
                    std::cerr << "\t" << std::setw(3) << i << " : " << *curr << std::endl;
                }
            }

            //! forward run \param seq a sequence
            template <typename SEQ> static inline
            void Forward( SEQ &seq )
            {
                std::cerr << "Test Forward/Mutable" << std::endl;
                Run(seq.begin(),seq.end());
            }

            //! forward const run \param seq a sequence
            template <typename SEQ> static inline
            void ForwardConst( const SEQ &seq )
            {
                std::cerr << "Test Forward/Const" << std::endl;
                Run(seq.begin(),seq.end());
            }

            //! reverse run \param seq a sequence
            template <typename SEQ> static inline
            void Reverse( SEQ &seq )
            {
                std::cerr << "Test Reverse/Mutable" << std::endl;
                Run(seq.rbegin(),seq.rend());
            }

            //! reverse const run \param seq a sequence
            template <typename SEQ> static inline
            void ReverseConst( const SEQ &seq )
            {
                std::cerr << "Test Reverse/Const" << std::endl;
                Run(seq.rbegin(),seq.rend());
            }

            //! all forward runs \param seq a sequence
            template <typename SEQ> static inline
            void AllForward( SEQ &seq )
            {
                Forward(seq);
                ForwardConst(seq);
            }

            //! all reverse runs \param seq a sequence
            template <typename SEQ> static inline
            void AllReverse( SEQ &seq )
            {
                Reverse(seq);
                ReverseConst(seq);
            }

            //! both mutable run forward/reverse \param seq a sequence
            template <typename SEQ> static inline
            void Both(SEQ &seq)
            {
                Forward(seq);
                Reverse(seq);
            }

            //! both const run forward/reverse \param seq a sequence
            template <typename SEQ> static inline
            void BothConst(const SEQ &seq)
            {
                ForwardConst(seq);
                ReverseConst(seq);
            }

            //! All runs \param seq a sequence
            template <typename SEQ> static inline
            void All(SEQ &seq)
            {
                std::cerr << "---- Testing All Iterators ----" << std::endl;
                AllForward(seq);
                AllReverse(seq);
            }

        };

    }

}

#endif // !Y_Container_Iter_Tests_Included

