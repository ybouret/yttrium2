
#include "y/container/contiguous.hpp"

#include "y/container/iter/linear.hpp"
#include "y/core/display.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"

#include "y/core/display.hpp"

namespace Yttrium
{






	template <typename T, template <typename> class CONTAINER>
	class LightArrayCommon : public Contiguous<CONTAINER, T>
	{
	public:
		Y_ARGS_EXPOSE(T, Type);
		inline virtual ~LightArrayCommon() noexcept {}


	protected:
		inline  LightArrayCommon(ConstType * const entry,
			const size_t      count) noexcept :
			bulk(count),
			item((ConstType *)Memory::Stealth::Address(entry) - 1)
		{
		}

	public:
		virtual size_t size() const noexcept { return bulk; }


	private:
		Y_Disable_Copy_And_Assign(LightArrayCommon);
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
		public LightArrayCommon<T, Readable>
	{
	public:
		Y_ARGS_EXPOSE(T, Type);
		inline ReadableLightArray(ConstType * const entry,
			const size_t      count) noexcept :
			LightArrayCommon<T, Readable>(entry, count)
		{
		}

		inline virtual ~ReadableLightArray() noexcept
		{
		}


	private:
		Y_Disable_Copy_And_Assign(ReadableLightArray);
	};


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




}
Y_UTEST(container_iterator)
{
	//Y<int, int> y;   // C3200

	Y<X, int> y;
	(void)y;

	int array[10];

	const size_t n = sizeof(array) / sizeof(array[0]);
	for (size_t i = 0; i < n; ++i) array[i] = int(i);


#if 0
	ReadableLightArray<int> arr(array, n);

	for (ReadableLightArray<int>::ConstIterator it = arr.begin(); it != arr.end(); ++it)
	{
		std::cerr << *it << std::endl;
	}


	std::cerr << arr << std::endl;
	Core::Display(std::cerr, arr.begin(), arr.size()) << std::endl;
#endif


}
Y_UDONE()
