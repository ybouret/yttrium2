
#include "y/stream/gzip/input.hpp"

namespace Yttrium
{
    namespace GZip
    {
        Input:: Input(const char * const fileName) :
        InputFile(fileName),
        InputStream(),
        buffer()
        {

        }


        Input:: Input(const String &fileName) :
        InputFile(fileName.c_str()),
        InputStream(),
        buffer()
        {

        }

        Input:: ~Input() noexcept
        {
            
        }


        bool Input:: query(char &c)
        {
            if(buffer.size()>0)
            {
                c = char( buffer.pullHead() );
                return true;
            }
            else
            {
                return query1(c);
            }
        }

        void Input::store(const char c)
        {
            buffer >> uint8_t(c);
        }


    }

}
