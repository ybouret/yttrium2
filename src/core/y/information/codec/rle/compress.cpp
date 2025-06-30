
#include "y/information/codec/rle/compress.hpp"
#include "y/stream/memory/static-output.hpp"
#include "y/object.hpp"
#include "y/type/destroy.hpp"


namespace Yttrium
{

    namespace Information
    {
        namespace RLE
        {

            class Compress:: Proc : public Object
            {
            public:
                inline explicit Proc() : count(0), match(0), enc64()
                {
                }

                inline virtual ~Proc() noexcept
                {
                }

                inline void reset() noexcept
                {
                    count = 0;
                    match = 0;
                }

                inline void emit( QCodec &q )
                {
                    if(count>0)
                    {
                        enc64.reset();
                        size_t         n = enc64.encode64(count); assert(n==enc64.length());
                        const uint8_t *p = (const uint8_t *)enc64.ro();
                        while(n-- > 0) q.qWrite( *(p++) );
                        q.qWrite(match);
                        reset();
                    }
                    assert(0==count);
                    assert(0==match);
                }

                inline void init(const uint8_t b) noexcept
                {
                    assert(0==count);
                    match = b;
                    count = 1;
                }

                inline void write(const char c, QCodec &q)
                {
                    const uint8_t b = uint8_t(c);
                    if(count<=0)
                    {
                        init(b);
                    }
                    else
                    {
                        assert(count>0);
                        if(b==match)
                        {
                            ++count;
                        }
                        else
                        {
                            emit(q);
                            init(b);
                        }
                    }
                }


                uint64_t              count; //!< successive count
                uint8_t               match; //!< of this match
                MemoryStaticOutput<9> enc64; //!< encode count

            private:
                Y_Disable_Copy_And_Assign(Proc);
            };



            Compress:: Compress() :
            QCodec(),
            proc( new Proc() )
            {
            }

            Compress:: ~Compress() noexcept
            {
                Destroy(proc);
            }

            void Compress:: reset() noexcept
            {
                qClear();
                proc->reset();
            }

            void Compress:: write(const char c)
            {
                assert(0!=proc);
                proc->write(c,*this);
            }

            void Compress:: flush()
            {
                assert(0!=proc);
                proc->emit(*this);
            }

            

        }
    }

}
