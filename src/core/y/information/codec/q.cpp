

#include "y/information/codec/q.hpp"
#include "y/protean/solo/heavy/list.hpp"
#include "y/object.hpp"

namespace Yttrium
{

    namespace Information
    {

        class QCodec:: Code : public Object
        {
        public:
            explicit Code() : Object(), list()
            {
            }

            virtual ~Code() noexcept
            {
            }

            List<char,SingleThreadedClass> list;


        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        QCodec:: ~QCodec() noexcept
        {
        }

        QCodec:: QCodec() noexcept : code( new Code() )
        {
        }

        bool QCodec:: query(char &C)
        {
            assert(0!=code);
            if( code->list.size() > 0 )
            {
                C = char( code->list.pullHead() );
                return true;
            }
            else
            {
                return false;
            }
        }

        void QCodec:: store(const char C)
        {
            assert(0!=code);
            code->list.pushHead(C);
        }

        void QCodec:: emit(const uint8_t byte)
        {
            code->list.pushTail(byte);
        }



    }

}

