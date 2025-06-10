
#include "y/container/contiguous.hpp"

#include "y/container/iter/linear.hpp"
#include "y/core/display.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"

#include "y/core/display.hpp"

namespace Yttrium
{

	template < template <typename> class CONTAINER, typename T>
	class LightArray : public Contiguous<CONTAINER, T>
	{
	public:
		Y_ARGS_EXPOSE(T, Type);


		inline  LightArray(ConstType * const entry,
			const size_t      count) noexcept :
			bulk(count),
			item((ConstType *)Memory::Stealth::Address(entry) - 1)
		{
		}

		inline virtual ~LightArray() noexcept {}


	public:
		virtual size_t size() const noexcept { return bulk; }


	private:
		Y_Disable_Copy_And_Assign(LightArray);
		const size_t      bulk;
		ConstType * const item;

		virtual ConstType & getItemAt(const size_t indx) const noexcept
		{
			assert(bulk > 0);
			assert(0 != item);
			return item[indx];
		}
	};



#if 0
	template <typename T> class ReadableLightArray :
		public LightArrayCommon<Readable,T>
	{
	public:
		Y_ARGS_EXPOSE(T, Type);
		typedef LightArrayCommon<Readable, T> Toto;
		inline ReadableLightArray(ConstType * const entry,
			const size_t      count) noexcept :
			Totot(entry, count)
		{
		}

		inline virtual ~ReadableLightArray() noexcept
		{
		}


	private:
		Y_Disable_Copy_And_Assign(ReadableLightArray);
	};

#endif

#if 0
	template <typename T> class WritableLightArray :
		public LightArrayCommon<T, Writable>
	{
	public:
		Y_ARGS_EXPOSE(T, Type);
		inline WritableLightArray(ConstType * const entry,
			const size_t      count) noexcept :
			LightArrayCommon<Readable, T>(entry, count)
		{
		}

		inline virtual ~WritableLightArray() noexcept
		{
		}


	private:
		Y_Disable_Copy_And_Assign(WritableLightArray);
	};
#endif


}

using namespace Yttrium;

namespace
{
	// C3200.cpp
	template<typename T>
	class X
	{
	};

	template<template<typename U> class T1, typename T2>
	class Y
	{
	};

	template <typename T>
	class Z : public Y<X,T>
	{

	};



}
Y_UTEST(container_iterator)
{
	//Y<int, int> y;   // C3200

	Y<X, int> y;
	(void)y;

	Z<int> z;
	(void)z;

	int array[10];

	const size_t n = sizeof(array) / sizeof(array[0]);
	for (size_t i = 0; i < n; ++i) array[i] = int(i);

	typedef LightArray<Readable, int> ReadOnlyArray;

#if 1
	ReadOnlyArray arr(array, n);

	for (ReadOnlyArray::ConstIterator it = arr.begin(); it != arr.end(); ++it)
	{
		std::cerr << *it << std::endl;
	}


	std::cerr << arr << std::endl;
	Core::Display(std::cerr, arr.begin(), arr.size()) << std::endl;
#endif


}
Y_UDONE()
