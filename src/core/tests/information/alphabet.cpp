#include "y/utest/run.hpp"

#include "y/information/pack/alphabet.hpp"

#include "y/object.hpp"
#include "y/memory/allocator.hpp"
#include <cstring>
#include "y/format/hexadecimal.hpp"
#include "y/format/binary.hpp"

using namespace Yttrium;

namespace Yttrium
{
    namespace  Information
    {

        namespace Pack
        {

           


            class Huffman
            {
            public:
                typedef Character::CodeType CodeType;
                typedef Alphabet::DataType  DataType;
                static const DataType MaxChars = Alphabet::EOS;
                static const DataType MaxNodes = 2*MaxChars;


                class Node
                {
                public:
                    Node(const Character * const);

                    Character * const leaf;
                    CodeType          code;
                    unsigned          bits;
                    Node *            left;
                    Node *            right;

                private:
                    Y_Disable_Copy_And_Assign(Node);
                    ~Node() noexcept;
                };

                Huffman();
                virtual ~Huffman() noexcept;


            private:
                Y_Disable_Copy_And_Assign(Huffman);
            };


        }
    }
}

Y_UTEST(info_alphabet)
{
    Information::Pack::Alphabet streaming( Information::Pack::Streaming );
    Information::Pack::Alphabet messaging( Information::Pack::Messaging );

    streaming.display(std::cerr);
    streaming.reduce();
    streaming.display(std::cerr);

    std::cerr << std::endl;
    messaging.display(std::cerr);
    messaging.reduce();
    messaging.display(std::cerr);


    std::cerr << std::endl;
    streaming.update('A');
    streaming.display(std::cerr);
    for(unsigned i=0;i<256;++i)
        streaming.update( (uint8_t)i );
    streaming.display(std::cerr);


}
Y_UDONE()

