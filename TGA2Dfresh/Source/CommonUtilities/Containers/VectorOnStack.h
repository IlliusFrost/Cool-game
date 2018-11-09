#pragma once
#include <array>
#include <assert.h>
#include <initializer_list>
#include "Macro.hpp"

namespace CommonUtilities
{
	template <typename Type, size_t size, typename CountType = unsigned short, bool UseSafeModeFlag = true>
	class VectorOnStack
	{
	public:
		VectorOnStack();
		VectorOnStack(const VectorOnStack& aVectorOnStack);
		VectorOnStack(const std::initializer_list<Type>& aInitList);
		~VectorOnStack();
		VectorOnStack & operator=(const VectorOnStack & aVectorOnStack);
		inline const Type& operator[](const CountType & aIndex) const;
		inline Type& operator[](const CountType & aIndex);
		inline void Add(const Type& aObject);
		inline void Insert(CountType aIndex, Type& aObject);
		inline void DeleteCyclic(Type& aObject);
		inline void DeleteCyclicAtIndex(CountType aItemNumber);
		inline void RemoveCyclic(const Type& aObject);
		inline void RemoveCyclicAtIndex(CountType aItemNumber);
		inline void Clear();
		inline void DeleteAll();
		inline CountType Size() const;
	private:
		CountType mySize;
		Type myVector[size];
	};
	template<typename Type, size_t size, typename CountType, bool UseSafeModeFlag>
	inline VectorOnStack<Type, size, CountType, UseSafeModeFlag>::VectorOnStack()
	{
		mySize = 0;
	}
	template<typename Type, size_t size, typename CountType, bool UseSafeModeFlag>
	inline VectorOnStack<Type, size, CountType, UseSafeModeFlag>::VectorOnStack(const VectorOnStack & aVectorOnStack)
	{
		mySize = aVectorOnStack.Size();
		operator=(aVectorOnStack);
	}
	template<typename Type, size_t size, typename CountType, bool UseSafeModeFlag>
	inline VectorOnStack<Type, size, CountType, UseSafeModeFlag>::VectorOnStack(const std::initializer_list<Type>& aInitList)
	{
		mySize = aInitList.size();
		if (UseSafeModeFlag)
		{
			for (int i = 0; i < mySize; ++i)
			{
				myVector[i] = *(aInitList.begin() + i);
			}
		}
		else
		{
			memcpy(&myVector, &aInitList, sizeof(Type) * mySize);
		}
	}
	template<typename Type, size_t size, typename CountType, bool UseSafeModeFlag>
	inline VectorOnStack<Type, size, CountType, UseSafeModeFlag>::~VectorOnStack()
	{
		mySize = 0;
	}
	template<typename Type, size_t size, typename CountType, bool UseSafeModeFlag>
	inline VectorOnStack<Type, size, CountType, UseSafeModeFlag> & VectorOnStack<Type, size, CountType, UseSafeModeFlag>::operator=(const VectorOnStack & aVectorOnStack)
	{
		if (mySize != aVectorOnStack.Size())
		{
			mySize = aVectorOnStack.Size();
		}

		if (UseSafeModeFlag)
		{
			for (int i = 0; i < mySize; ++i)
			{
				myVector[i] = aVectorOnStack[i];
			}
		}
		else
		{
			memcpy(&myVector, &aVectorOnStack.myVector, sizeof(Type) * mySize);
		}
		return *this;
	}
	template<typename Type, size_t size, typename CountType, bool UseSafeModeFlag>
	inline const Type & VectorOnStack<Type, size, CountType, UseSafeModeFlag>::operator[](const CountType & aIndex) const
	{
		assert(aIndex >= 0 && "Out of bounds, index is less than 0!");
		assert(aIndex < mySize && "Index is out of bounds!");
		return myVector[aIndex];
	}
	template<typename Type, size_t size, typename CountType, bool UseSafeModeFlag>
	inline Type & VectorOnStack<Type, size, CountType, UseSafeModeFlag>::operator[](const CountType & aIndex)
	{
		assert(aIndex >= 0 && "Out of bounds, index is less than 0!");
		assert(aIndex < mySize && "Index is out of bounds!");
		return myVector[aIndex];
	}
	template<typename Type, size_t size, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::Add(const Type & aObject)
	{
		assert(mySize < size && "Vector already full!");

		myVector[mySize] = aObject;
		++mySize;
	}
	template<typename Type, size_t size, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::Insert(CountType aIndex, Type & aObject)
	{
		assert(mySize < size && "Vector already full!");
		assert(aIndex >= 0 && "Out of bounds, index is less than 0!");
		assert(aIndex < mySize && "Index is out of bounds!");

		for (int i = mySize; i > aIndex - 1; --i)
		{
			myVector[i + 1] = myVector[i];
		}
		myVector[aIndex] = aObject;
		++mySize;
	}
	template<typename Type, size_t size, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::DeleteCyclic(Type & aObject)
	{
		for (int i = 0; i < mySize - 1; ++i)
		{
			if (myVector[i] == aObject)
			{
				DeleteCyclicAtIndex(i);
				return;
			}
		}
	}
	template<typename Type, size_t size, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::DeleteCyclicAtIndex(CountType aItemNumber)
	{
		assert(aItemNumber < mySize && "Index is out of bounds!");

		delete myVector[aItemNumber];
		myVector[aItemNumber] = myVector[mySize - 1];
		myVector[mySize - 1] = nullptr;
		--mySize;
		return;
	}
	template<typename Type, size_t size, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::RemoveCyclic(const Type & aObject)
	{
		for (int i = 0; i < mySize; ++i)
		{
			if (myVector[i] == aObject)
			{
				RemoveCyclicAtIndex(i);
				return;
			}
		}
	}
	template<typename Type, size_t size, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::RemoveCyclicAtIndex(CountType aItemNumber)
	{
		assert(aItemNumber < mySize && "Tried to delete an element out of range!");
		myVector[aItemNumber] = myVector[mySize - 1];
		myVector[mySize - 1] = 0;
		--mySize;
	}
	template<typename Type, size_t size, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::Clear()
	{
		mySize = 0;
	}
	template<typename Type, size_t size, typename CountType, bool UseSafeModeFlag>
	inline void VectorOnStack<Type, size, CountType, UseSafeModeFlag>::DeleteAll()
	{
		for (int i = 0; i < mySize; ++i)
		{
			SAFE_DELETE(myVector[i]);
		}
	}
	template<typename Type, size_t size, typename CountType, bool UseSafeModeFlag>
	inline CountType VectorOnStack<Type, size, CountType, UseSafeModeFlag>::Size() const
	{
		return mySize;
	}
};