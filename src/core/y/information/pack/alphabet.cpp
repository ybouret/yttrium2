
#include "y/information/pack/alphabet.hpp"
#include "y/format/binary.hpp"
#include "y/format/hexadecimal.hpp"
#include <iomanip>
#include "y/object.hpp"
#include "y/memory/allocator.hpp"

namespace Yttrium
{

    namespace Information
    {
        namespace Pack
        {
            std::ostream & operator<<(std::ostream &os, const Character &ch)
            {
                switch(ch.data)
                {
                    case Alphabet::NYT: os << "NYT"; break;
                    case Alphabet::EOS: os << "EOS"; break;
                    default:
                        assert(ch.data<256);
                        const uint8_t b = (uint8_t)ch.data;
                        if(b<32||b>126)
                        {
                            os << Hexadecimal(b).c_str() + 1;
                        }
                        else
                        {
                            os << "'" << (char)b << "'";
                        }
                }
                os << ": #" << std::setw(3) << ch.bits << ": " << Binary(ch.code,ch.bits);
                os << " [" << ch.freq << "]";
                return os;
            }

            Alphabet:: Alphabet(const Category c) :
            category(c),
            universe(Chars+category),
            detected(0),
            totality(0),
            encoding(),
            ch_count(universe),
            ch_bytes(0),
            database(Object::AllocatorInstance().acquireAs<Character>(ch_count,ch_bytes)),
            nyt(database+NYT),
            eos( (Messaging==category) ? database + EOS : 0)
            {
                setup();
            }

            Alphabet:: ~Alphabet() noexcept
            {
                Object::AllocatorLocation().releaseAs(Coerce(database),ch_count,ch_bytes);
            }


            void Alphabet:: setup() noexcept
            {

                for(DataType i=0;i<Chars;++i)
                {
                    Character &ch = database[i];
                    Coerce(ch.data) = i;
                    ch.code = i;
                    ch.bits = 8;
                }

                for(DataType i=Chars;i<universe;++i)
                {
                    Character &ch = database[i];
                    Coerce(ch.data) = i;
                    ch.code = i;
                    ch.bits = 9;
                }

                cntrl();
            }

            void Alphabet:: reset() noexcept
            {
                encoding.reset();
                totality = 0;
                detected = 0;
                for(DataType i=0;i<Chars;++i)          database[i].reset(8);
                for(DataType i=Chars;i<universe;++i)   database[i].reset(9);
                cntrl();
            }

            void Alphabet:: cntrl() noexcept
            {
                for(DataType i=Chars;i<universe;++i) encoding.pushTail(database+i);
            }


            void Alphabet:: display(std::ostream &os) const
            {
#if 0
                for(DataType i=0;i<universe;++i)
                {
                    const Character &ch = database[i];
                    if(ch.freq>0)
                        os << ch << std::endl;
                }
#endif

                for(const Character *ch=encoding.head;ch;ch=ch->next)
                {
                    os << *ch << std::endl;
                }
                std::cerr << "encoding=" << encoding.size << std::endl;
                std::cerr << "totality=" << totality      << std::endl;
            }

            void Alphabet:: reduce() noexcept
            {
                totality = 0;
                for(Character *ch=encoding.head;ch;ch=ch->next)
                    totality += ch->reduce();
            }

#if !defined(NDEBUG)
            static inline SignType ByDecreasingFreq(const Character * const lhs,
                                                    const Character * const rhs) noexcept
            {
                assert(lhs); assert(rhs);
                return Sign::Of(rhs->freq,lhs->freq);
            }
#endif // !defined(NDEBUG)

            Alphabet & Alphabet:: operator<<(const uint8_t i) noexcept
            {
                {
                    Character * const ch = database+i;
                    if(ch->freq<=0) {
                        if(++detected>=Chars)
                            (void)encoding.pop(nyt);
                        encoding.pushTail(ch);
                    }
                    ++ch->freq;
                    while(ch->prev && ch->prev->freq < ch->freq)
                        encoding.towardsHead(ch);
                    while(ch->next && ch->freq < ch->next->freq)
                        encoding.towardsTail(ch);
                    assert(encoding.isOrderedBy(ByDecreasingFreq, Sign::LooselyIncreasing ));

                }


                if(totality>=MaxFreq) {
                    reduce();
                }
                else
                    ++totality;
                return *this;
            }
        }

    }

}
