#include "y/utest/run.hpp"

#include "y/object.hpp"
#include "y/memory/allocator.hpp"
#include "y/ostream-proto.hpp"
#include <cstring>
#include "y/ascii/printable.hpp"
#include "y/core/linked/list/raw.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/format/binary.hpp"

using namespace Yttrium;

namespace Yttrium
{
    namespace  Information
    {

        enum Category
        {
            Streaming=1, //!< +NYT, -EOS
            Messaging=2  //!< +NYT, +EOS
        };

        class Character
        {
        public:
            typedef uint16_t DataType; //!< alias for bytes + control
            typedef uint32_t FreqType; //!< alias
            typedef uint64_t CodeType; //!< alias

            Y_OSTREAM_PROTO(Character);

            const DataType data;
            CodeType       code;
            unsigned       bits;
            FreqType       freq;
            Character *    next;
            Character *    prev;

            void     reset(const unsigned n, const FreqType f) noexcept;
            FreqType reduce() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Character);
            Character();
            ~Character() noexcept;
        };



        void Character:: reset(const unsigned n, const FreqType f) noexcept
        {
            code = data;
            bits = n;
            freq = f;
            next = 0;
            prev = 0;
        }

        Character::FreqType Character:: reduce() noexcept
        {
            static const FreqType one = 1;
            assert(freq>0);
            return ( (freq >>= 1) |= one );
        }


        class Alphabet
        {
        public:
            typedef Character::DataType  DataType;
            typedef Character::FreqType  FreqType;
            typedef Character::CodeType  CodeType;
            typedef RawListOf<Character> CharList;

            static const DataType Chars = 256;
            static const DataType NYT   = Chars;
            static const DataType EOS   = NYT+1;
            static const FreqType MaxFreq = IntegerFor<FreqType>::Maximum;

            explicit Alphabet(const Category);
            virtual ~Alphabet() noexcept;


            void update(const uint8_t i) noexcept;
            void display(std::ostream &) const;
            void reduce() noexcept;


            const Category    category;
            const DataType    universe;
            DataType          detected;   //!< up to Codes to remove NYT
            FreqType          totality;   //!< current sum of frequencies
            CharList          encoding;   //!< encoding chars + control
        private:
            size_t            ch_count;
            size_t            ch_bytes;
        public:
            Character * const database;   //!< database
            Character * const nyt;
            Character * const eos;

        private:
            Y_Disable_Copy_And_Assign(Alphabet);




            void setup() noexcept; //!< initial setup on a clean workspace
            void reset() noexcept; //!< reset all
            void cntrl() noexcept; //!< register controls in encoding

        };


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
        totality(category),
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
                ch.freq = 1;
            }

            cntrl();
        }

        void Alphabet:: reset() noexcept
        {
            encoding.reset();
            totality = category;
            detected = 0;
            for(DataType i=0;i<Chars;++i)          database[i].reset(8,0);
            for(DataType i=Chars;i<universe;++i)   database[i].reset(9,1);
            cntrl();
        }

        void Alphabet:: cntrl() noexcept
        {
            for(DataType i=Chars;i<universe;++i) encoding.pushTail(database+i);
        }


        void Alphabet:: display(std::ostream &os) const
        {
            for(DataType i=0;i<universe;++i)
            {
                const Character &ch = database[i];
                if(ch.freq>0)
                    os << ch << std::endl;
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

        void Alphabet:: update(const uint8_t i) noexcept
        {
            {
                Character * const ch = database+i;
                if(ch->freq<=0) {
                    if(++detected>=Chars) (void)encoding.pop(nyt);
                    encoding.pushTail(ch);
                }
                ++ch->freq;
            }
            if(totality>=MaxFreq) {
                reduce();
            }
        }


    }
}

Y_UTEST(info_alphabet)
{
    Information::Alphabet streaming( Information::Streaming );
    Information::Alphabet messaging( Information::Messaging );

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

