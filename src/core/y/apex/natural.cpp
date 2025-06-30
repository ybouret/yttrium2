
#include "y/apex/natural.hpp"
#include "y/apex/block/model.hpp"
#include "y/type/destroy.hpp"
#include "y/string.hpp"
#include "y/hexadecimal.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{
    namespace Apex
    {
        OpsMode Natural::Ops = Ops32_64;

        Natural:: Natural() : Number(),
        code( new Model(0, Model::SmallView[Ops]) )
        {
        }

        Natural:: Natural(const natural_t n) : Number(),
        code( new Model(n) )
        {

        }

        Natural:: Natural(Model * const model) noexcept :
        Number(),
        code( model )
        {
            assert(0!=model);
        }


        Natural & Natural:: operator=(const natural_t n) noexcept
        {
            code->ldz(View64);
            {
                Block<uint64_t> &b64 = code->get<uint64_t>();
                b64.data[0] = n;
                b64.size    = 1;
            }
            code->update();
            return (*this);
        }


        Natural:: ~Natural() noexcept
        {
            Destroy(code);
        }


        static inline size_t saveModel(Model &m, OutputStream &fp)
        {
            return m.save(fp);
        }

        size_t Natural:: serialize(OutputStream &fp) const
        {
            assert(0!=code);
            AutoPtr<Model> p;
            Model *        m = Coerce(code); if(View8!=code->view) { m = new Model(*m,View8); p = m; }
            return saveModel(*m,fp);
        }

        Natural:: Natural(const Natural &other) :
        Number(),
        code( new Model(*other.code,Model::SmallView[Ops]) )
        {

        }

        Natural & Natural:: operator=(const Natural &other)
        {

            if(this != &other)
            {
                Model &       target = *code;
                const Model & source = *other.code;
                if(target.space>=source.bytes)
                {
                    target.cpy(source);
                }
                else
                {
                    Model * temp = new Model(source,Model::SmallView[Ops]);
                    delete  code;
                    Coerce(code) = temp;
                }
            }
            return *this;
        }


        Natural :: Natural(const TwoToThePowerOf_ &, const size_t n) :
        code( new Model( SizeFor<uint8_t>::From(n+1), View8) )
        {
            assert(View8==code->view);
            {
                static const uint8_t bit[8] = { 1, 2, 4, 8, 16, 32, 64, 128};
                Block<uint8_t> &     blk = code->get<uint8_t>();
                const size_t         msb = n>>3;
                blk.data[msb] = bit[n&7];
                blk.size = msb+1;
            }
            code->update();
        }

        namespace
        {
            static inline String BlockHexString(const Model &model)
            {
                String res;
                assert(View8==model.view);
                const Block<uint8_t> &b = model.get<uint8_t>();
                size_t                i = b.size;
                if(i<=0)
                {
                    res = '0';
                }
                else
                {
                    while(i-- > 0)
                    {
                        res << Hexadecimal::LowerByte[b.data[i]];
                    }
                    assert(res.size()>0);
                    if('0' == *res.head() )
                    {
                        res.popHead();
                    }
                }
                return  res;
            }
        }

        String Natural:: hexString() const
        {
            AutoPtr<Model> p;
            Model *        m = Coerce(code); if(View8!=code->view) { m = new Model(*m,View8); p = m; }
            return BlockHexString(*m);
        }

        std::ostream & operator<<(std::ostream &os, const Natural &n)
        {
            const String s = n.hexString();
            return os << s;
        }


        Natural & Natural:: xch(Natural &other) noexcept
        {
            CoerceSwap(code,other.code);
            return *this;
        }

        Natural:: Natural(InputStream &fp, const char * const varName) :
        Number(),
        code( Model::Load(fp, Model::SmallView[Ops], varName) )
        {

        }


    }
    
}

#include "y/random/bits.hpp"
namespace Yttrium
{
    namespace Apex
    {
        Natural:: Natural(Random::Bits &ran, const size_t numBits) :
        Number(),
        code(0)
        {
            if(numBits>0)
            {
                {
                    const size_t     size = SizeFor<uint8_t>::From(numBits); assert(size>0);
                    Block<uint8_t> & blk  = (Coerce(code) = new Model(size,View8))->get<uint8_t>();
                    const size_t     msb  = (blk.size=size)-1;
                    uint8_t * const  ptr  = blk.data;
                    for(size_t i=0;i<size;++i) ptr[i] = ran.to<uint8_t>(8);
                    ptr[msb] = ran.to<uint8_t>(numBits - (msb<<3));
                }
                code->update();
                assert(numBits==code->bits);
            }
            else
            {
                Coerce(code) = new Model(0, Model::SmallView[Ops] );
            }
        }

    }
}

