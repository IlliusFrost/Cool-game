#pragma once
#include <assert.h>
#include <array>
#include <initializer_list>
#include "Macro.hpp"

namespace CommonUtilities
{
	template <typename T, size_t size>
	class StaticArray
	{
	public:
		StaticArray();
		StaticArray(const StaticArray& aStaticArray);
		StaticArray(const std::initializer_list<T>& aInitList);
		~StaticArray();
		StaticArray& operator=(const StaticArray& aStaticArray);
		inline const T& operator[](const int& aIndex) const;
		inline T& operator[](const int& aIndex);

		// Utility functions
		inline void Insert(int aIndex, T& aObject);
		inline void DeleteAll();

	private:
		T myArray[size];
	};

	template<typename T, size_t size>
	inline StaticArray<T, size>::StaticArray()
	{

	}
	template<typename T, size_t size>
	inline StaticArray<T, size>::StaticArray(const StaticArray & aStaticArray)
	{
		for (int i = 0; i < size; ++i)
		{
			myArray[i] = aStaticArray[i];
		}
	}

	template<typename T, size_t size>
	inline StaticArray<T, size>::StaticArray(const std::initializer_list<T>& aInitList)
	{
		assert(size >= aInitList.size() && "Your initalizer list has more elements than your array.");
		for (int i = 0; i < aInitList.size(); ++i)
		{
			myArray[i] = *(aInitList.begin() + i);
		}
	}

	template<typename T, size_t size>
	inline StaticArray<T, size>::~StaticArray()
	{

	}

	template<typename T, size_t size>
	inline StaticArray<T, size> & StaticArray<T, size>::operator=(const StaticArray & aStaticArray)
	{
		for (int i = 0; i < size; ++i)
		{
			myArray[i] = aStaticArray[i];
		}
		return *this;
	}

	template<typename T, size_t size>
	inline const T & StaticArray<T, size>::operator[](const int & aIndex) const
	{
		assert(aIndex >= 0 && "Out of bounds, index is less than 0!");
		assert(aIndex < size && "Index is out of bounds!");
		return myArray[aIndex];
	}

	template<typename T, size_t size>
	inline T & StaticArray<T, size>::operator[](const int & aIndex)
	{
		assert(aIndex >= 0 && "Out of bounds, index is less than 0!");
		assert(aIndex < size && "Index is out of bounds!");
		return myArray[aIndex];
	}

	template<typename T, size_t size>
	inline void StaticArray<T, size>::Insert(int aIndex, T & aObject)
	{
		assert(aIndex >= 0 && "Out of bounds, index is less than 0!");
		assert(aIndex < size && "Index is out of bounds!");

		for (int i = size - 1; i > aIndex; --i)
		{
			myArray[i] = myArray[i - 1];
		}
		myArray[aIndex] = aObject;
	}

	template<typename T, size_t size> 
	inline void StaticArray<T, size>::DeleteAll()
	{
		for (int i = 0; i < size; ++i)
		{
			SAFE_DELETE(myArray[i]);
		}
	}
}