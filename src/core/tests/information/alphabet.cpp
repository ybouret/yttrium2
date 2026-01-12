#include "y/utest/run.hpp"
#include "y/information/pack/alphabet.hpp"

using namespace Yttrium;



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
    streaming << 'A';
    streaming.display(std::cerr);
    for(unsigned i=0;i<256;++i)
        streaming <<  (uint8_t)i;
    streaming.display(std::cerr);
    

}
Y_UDONE()

