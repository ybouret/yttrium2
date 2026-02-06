
#include "y/information/pack/alphabet.hpp"
#include "y/format/binary.hpp"
#include "y/format/hexadecimal.hpp"
#include <iomanip>
#include "y/memory/stealth.hpp"

namespace Yttrium
{

	namespace Information
	{
		namespace Pack
		{
			std::ostream& operator<<(std::ostream& os, const Character& ch)
			{
				switch (ch.data)
				{
				case Alphabet::NYT: os << "NYT"; break;
				case Alphabet::EOS: os << "EOS"; break;
				default:
					assert(ch.data < 256);
					const uint8_t b = (uint8_t)ch.data;
					if (b < 32 || b>126)
					{
						os << Hexadecimal(b).c_str() + 1;
					}
					else
					{
						os << "'" << (char)b << "'";
					}
				}
				os << ": #" << std::setw(3) << ch.bits << ": " << Binary(ch.code, ch.bits);
				os << " [" << ch.freq << "]";
				return os;
			}


			static inline Alphabet::DataType Cat2Universe(const Category c) noexcept
			{
				switch (c)
				{
				case Streaming: return Alphabet::Chars + Streaming;
				case Messaging: return Alphabet::Chars + Messaging;
				}
				return 0; // never get here
			}

			Alphabet::Alphabet(const Category c) :
				category(c),
				universe(Cat2Universe(c)),
				writeNYT(false),
				detected(0),
				totality(0),
				encoding(),
				database(0),
				nyt(0),
				eos(0),
				wksp()
			{
				Coerce(database) = static_cast<Character*>(Y_Memory_BZero(wksp));
				assert(Memory::Stealth::Are0(wksp, sizeof(wksp)));
				assert(Memory::Stealth::Are0(database, InnerBytes));

				switch (category)
				{
				case Messaging: Coerce(eos) = database + EOS; // FALLTHRU
				case Streaming: Coerce(nyt) = database + NYT; break;
				}
				setup();
			}

			Alphabet:: ~Alphabet() noexcept
			{
			}


			void Alphabet::setup() noexcept
			{

				for (DataType i = 0; i < Chars; ++i)
				{
					Character& ch = database[i];
					Coerce(ch.data) = i;
					ch.code = i;
					ch.bits = 8;
				}

				for (DataType i = Chars; i < universe; ++i)
				{
					Character& ch = database[i];
					Coerce(ch.data) = i;
					ch.code = i;
					ch.bits = 9;
				}

				cntrl();
			}

			void Alphabet::reset() noexcept
			{
				encoding.reset();
				totality = 0;
				detected = 0;
				writeNYT = false;
				for (DataType i = 0; i < Chars; ++i)          database[i].reset(8);
				for (DataType i = Chars; i < universe; ++i)   database[i].reset(9);
				cntrl();
			}

			void Alphabet::cntrl() noexcept
			{
				for (DataType i = Chars; i < universe; ++i)
				{
					assert(0 == database[i].next);
					assert(0 == database[i].prev);
					encoding.pushTail(database + i);
				}
			}


			void Alphabet::display(std::ostream& os) const
			{
				for (const Character* ch = encoding.head; ch; ch = ch->next)
				{
					os << *ch << std::endl;
				}
				std::cerr << "encoding=" << encoding.size << std::endl;
				std::cerr << "totality=" << totality << std::endl;
			}

			void Alphabet::reduce() noexcept
			{
				totality = 0;
				for (Character* ch = encoding.head; ch; ch = ch->next)
					totality += ch->reduce();
			}

#if !defined(NDEBUG)
			static inline SignType ByDecreasingFreq(const Character* const lhs,
				const Character* const rhs) noexcept
			{
				assert(lhs); assert(rhs);
				return Sign::Of(rhs->freq, lhs->freq);
			}
#endif // !defined(NDEBUG)

			Alphabet& Alphabet:: operator<<(const uint8_t i) noexcept
			{

				// detect first inserted
				if (totality <= 0) writeNYT = true;

				// update
				{
					Character* const ch = database + i;
					if (ch->freq <= 0) {
						if (++detected >= Chars)
						{
							writeNYT = false;
							(void)encoding.pop(nyt);
						}
						encoding.pushTail(ch);
					}
					++ch->freq;
					while (ch->prev && ch->prev->freq < ch->freq)
						encoding.towardsHead(ch);
					while (ch->next && ch->freq < ch->next->freq)
						encoding.towardsTail(ch);
					assert(encoding.isOrderedBy(ByDecreasingFreq, Sign::LooselyIncreasing));

				}

				// adjust
				if (totality >= MaxFreq) {
					reduce();
				}
				else
					++totality;
				return *this;
			}
		}

	}

}

#include "y/stream/io/bits.hpp"

namespace Yttrium
{

	namespace Information
	{
		namespace Pack
		{
			void Alphabet::emit(IO::Bits& bits, const uint8_t byte, IO::Bits& pool) const
			{
				const Character& ch = database[byte];
				if (writeNYT && ch.freq <= 0)
					emit(bits, *nyt, pool);
				emit(bits, ch, pool);
			}


			void Alphabet::emit(IO::Bits& bits,
				const Character& ch,
				IO::Bits& pool) const
			{
				(void)bits.push<CodeType>(ch.code, ch.bits, pool);
			}



		}

	}

}
