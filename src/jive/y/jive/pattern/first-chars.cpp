
#include "y/jive/pattern/first-chars.hpp"
#include "y/ascii/printable.hpp"
#include "y/calculus/bits-in.hpp"
#include <iostream>
#include <cstring>
#include <cassert>

namespace Yttrium
{
	namespace Jive
	{
		FirstChars::FirstChars() noexcept :
			size(0),
			data()
		{
			free();
			assert(0 == Calculus::BitsIn::Block(data, sizeof(data)));
		}


		void FirstChars::free() noexcept
		{
			memset(data, 0, sizeof(data));
			Coerce(size) = 0;
		}

		void FirstChars::all() noexcept
		{
			memset(data, 0xff, sizeof(data));
			Coerce(size) = 256;
		}


		FirstChars::FirstChars(const FirstChars &fc) noexcept :
			size(fc.size),
			data()
		{
			memcpy(data, fc.data, sizeof(data));
		}

		FirstChars & FirstChars:: operator=(const FirstChars &fc) noexcept
		{
			Coerce(size) = fc.size;
			memmove(data, fc.data, sizeof(data));
			return *this;
		}


		static const uint8_t fcbit[8] = { 1,2,4,8,16,32,64,128 };

		bool FirstChars::getbit(const uint8_t b) const noexcept
		{
			return 0 != (data[b >> 3] & fcbit[b & 7]);
		}

		void FirstChars::setbit(const uint8_t b) noexcept
		{
			(data[b >> 3] |= fcbit[b & 7]);
		}

		static const uint8_t fcmsk[8] = { 255 - 1,255 - 2,255 - 4,255 - 8,255 - 16,255 - 32,255 - 64,255 - 128 };


		void FirstChars::clrbit(const uint8_t b) noexcept
		{
			data[b >> 3] &= fcmsk[b & 7];
		}



		void FirstChars::add(const uint8_t b) noexcept
		{
			if (!getbit(b))
			{
				++Coerce(size);
				setbit(b);
				assert(size == Calculus::BitsIn::Block(data, sizeof(data)));
			}
		}

		void FirstChars::add(uint8_t a, uint8_t b) noexcept
		{
			if (a > b) Swap(a, b);
			const unsigned A(a), B(b);
			for (unsigned i = A; i <= B; ++i)
			{
				add(uint8_t(i));
			}
		}

		void FirstChars::sub(const uint8_t b) noexcept
		{
			if (getbit(b))
			{
				clrbit(b);
				--Coerce(size);
				assert(size == Calculus::BitsIn::Block(data, sizeof(data)));
			}
		}


		void FirstChars::sub(uint8_t a, uint8_t b) noexcept
		{
			if (a > b) Swap(a, b);
			const unsigned A(a), B(b);
			for (unsigned i = A; i <= B; ++i)
			{
				sub(uint8_t(i));
			}
		}

		FirstChars & FirstChars:: operator +=(const FirstChars &fc) noexcept
		{

			for (size_t i = 0; i < sizeof(data); ++i)
			{
				data[i] |= fc.data[i];
			}
			Coerce(size) = Calculus::BitsIn::Block(data, sizeof(data));
			return *this;
		}

		FirstChars & FirstChars:: operator -=(const FirstChars &fc) noexcept
		{

			for (size_t i = 0; i < sizeof(data); ++i)
			{
				data[i] &= ~fc.data[i];
			}
			Coerce(size) = Calculus::BitsIn::Block(data, sizeof(data));
			return *this;
		}


		unsigned FirstChars::findLowerBit(unsigned i) const noexcept
		{
			assert(i < 256);
			for (; i < 256; ++i)
			{
				if (getbit((uint8_t)i))
					break;
			}
			return i;
		}

		unsigned FirstChars::findUpperBit(unsigned i) const noexcept
		{
			assert(i < 256);
			assert(getbit(i));
			for (++i; i < 256; ++i)
			{
				if (!getbit((uint8_t)i))
					break;
			}
			return i - 1;
		}

		void FirstChars::run(Proc proc, void * const args) const
		{
			assert(proc);
			unsigned lower = 0;

			while (lower < 256)
			{
				lower = findLowerBit(lower); if (lower >= 256) return;
				const unsigned upper = findUpperBit(lower);
				proc(uint8_t(lower), uint8_t(upper), args);
				lower = upper + 1;
			}


		}

		void FirstChars::Print(const uint8_t lower, const uint8_t upper, void * args)
		{
			assert(upper >= lower);
			assert(args);
			std::ostream &os = *(std::ostream *)args;
			os << '[';
			if (lower >= upper)
			{
				os << ASCII::Printable::Char[lower];
			}
			else
			{
				os << ASCII::Printable::Char[lower] << '-' << ASCII::Printable::Char[upper];
			}
			os << ']';
		}

		std::ostream & operator<<(std::ostream &os, const FirstChars &fc)
		{
			fc.run(FirstChars::Print, &os);
			return os;
		}


	}

}

