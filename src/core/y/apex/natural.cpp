
#include "y/apex/natural.hpp"
#include "y/apex/block/model.hpp"
#include "y/type/destroy.hpp"
#include "y/string.hpp"
#include "y/hexadecimal.hpp"

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
            if(View8==code->view)
            {
                return saveModel(*code,fp);
            }
            else
            {
                Model::Pointer m(*code,View8);
                return saveModel(*m,fp);
            }
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
            static inline std::ostream & BlockPrintHex(std::ostream &os, const Model &model)
            {
                String res;
                assert(View8==model.view);
                const Block<uint8_t> &b = model.get<uint8_t>();
                size_t                i = b.size;
                if(i<=0)
                {
                    res = "0x0";
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
                    res >> "0x";
                }
                return os << res;
            }
        }

        std::ostream & Natural:: printHex(std::ostream &os) const
        {
            if(code->view == View8)
                return BlockPrintHex(os,*code);
            else
            {
                const Model::Pointer temp(*code,View8);
                return BlockPrintHex(os,*temp);
            }
        }

        std::ostream & operator<<(std::ostream &os, const Natural &n)
        {
            return n.printHex(os);
        }


    }
    
}
