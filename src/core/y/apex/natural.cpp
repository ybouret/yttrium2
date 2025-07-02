
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
        Y_Shallow_Impl(Attach);

        OpsMode Natural::Ops = Ops32_64;

        Natural:: Natural() : Number(),
        code( new Model(0, Model::SmallView[Ops]) )
        {
        }

        Natural:: Natural(const natural_t n) : Number(),
        code( new Model(n) )
        {
            relax();
        }


        void Natural:: alter(const ViewType view) noexcept
        {
            assert(0!=code);
            code->set( view );

        }

        void Natural:: relax() noexcept
        {
            alter(  Model::SmallView[Ops] );
        }

        size_t Natural:: bytes() const noexcept
        {
            assert(0!=code);
            return code->bytes;
        }

        size_t Natural:: bits() const noexcept
        {
            assert(0!=code);
            return code->bits;
        }



        Natural:: Natural(const Attach_&, Model * const model) noexcept :
        Number(),
        code( model )
        {
            assert(0!=model);
            relax();
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
            relax();
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
                    relax();
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
            relax();
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
            relax();
            return *this;
        }

        uint64_t Natural:: ls64() const noexcept
        {
            return code->api().little();
        }


        Natural:: Natural(InputStream &fp, const char * const varName) :
        Number(),
        code( Model::Load(fp,Model::SmallView[Ops],varName) )
        {

        }

       void Natural:: ldz() noexcept
        {
            assert(0!=code);
            (void) code->ldz(Model::SmallView[Ops]);
        }

        void Natural:: ld1() noexcept
        {
            assert(0!=code);
            (void) code->ld1(Model::SmallView[Ops]);
        }

        Natural Natural:: abs() const
        {
            return *this;
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
                relax();
                assert(numBits==code->bits);
            }
            else
            {
                Coerce(code) = new Model(0, Model::SmallView[Ops] );
            }
        }

    }
}

