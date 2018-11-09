#pragma once
#include <assert.h>

namespace CommonUtilities
{
	template<typename ObjectType, typename SizeType = unsigned short>
	class GrowingArray
	{
	public:
		GrowingArray();
		GrowingArray(SizeType aNrOfRecommendedItems, bool
			aUseSafeModeFlag = true);
		GrowingArray(const GrowingArray& aGrowingArray);
		GrowingArray(GrowingArray&& aGrowingArray);
		~GrowingArray();
		GrowingArray& operator=(const GrowingArray& aGrowingArray);
		GrowingArray& operator=(GrowingArray&& aGrowingArray);
		void Init(SizeType aNrOfRecomendedItems, bool aUseSafeModeFlag = true);
		void ReInit(SizeType aNrOfRecomendedItems, bool aUseSafeModeFlag = true);
		inline ObjectType& operator[](const SizeType& aIndex);
		inline const ObjectType& operator[](const SizeType& aIndex) const;
		inline void Add(const ObjectType& aObject);
		inline void Insert(SizeType aIndex, const ObjectType& aObject);
		inline void DeleteCyclic(const ObjectType& aObject);
		inline void DeleteCyclicAtIndex(SizeType aItemNumber);
		inline void RemoveCyclic(const ObjectType& aObject);
		inline void RemoveCyclicAtIndex(SizeType aItemNumber);
		inline SizeType Find(const ObjectType& aObject);
		inline ObjectType& GetLast();
		inline const ObjectType& GetLast() const;
		static const SizeType FoundNone = -1;
		inline void RemoveAll();
		inline void DeleteAll();
		void Optimize();
		__forceinline SizeType Size() const;
		inline void Reserve(SizeType aNewSize);
		inline void Resize(SizeType aNewSize);
	private:
		ObjectType* myArray;
		SizeType myCurrentSize;
		SizeType myMaxSize;
		bool myUseSafeMode;
		bool myIsInitialized;
	};
	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>::GrowingArray() :
		myArray(nullptr),
		myCurrentSize(0),
		myMaxSize(0),
		myUseSafeMode(false),
		myIsInitialized(false)
	{
	}
	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>::GrowingArray(SizeType aNrOfRecommendedItems, bool aUseSafeModeFlag) :
		myIsInitialized(nullptr)
	{
		Init(aNrOfRecommendedItems, aUseSafeModeFlag);
	}
	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>::GrowingArray(const GrowingArray & aGrowingArray) :
		myIsInitialized(false),
		myArray(nullptr)
	{
		operator=(aGrowingArray);
	}
	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>::GrowingArray(GrowingArray && aGrowingArray)
	{
		operator=(aGrowingArray);
	}
	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType>::~GrowingArray()
	{
		delete[] myArray;
		myArray = nullptr;
	}
	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType> & GrowingArray<ObjectType, SizeType>::operator=(const GrowingArray & aGrowingArray)
	{
		delete[] myArray;
		myMaxSize = aGrowingArray.myMaxSize;
		myArray = new ObjectType[myMaxSize];
		myUseSafeMode = aGrowingArray.myUseSafeMode;
		if (myUseSafeMode)
		{
			for (SizeType index = 0; index < aGrowingArray.myCurrentSize; ++index)
			{
				myArray[index] = aGrowingArray.myArray[index];
			}
		}
		else
		{
			memcpy(myArray, aGrowingArray.myArray,
				sizeof(ObjectType) * aGrowingArray.myCurrentSize);
		}
		myCurrentSize = aGrowingArray.myCurrentSize;
		myIsInitialized = aGrowingArray.myIsInitialized;
		return *this;
	}
	template<typename ObjectType, typename SizeType>
	inline GrowingArray<ObjectType, SizeType> & GrowingArray<ObjectType, SizeType>::operator=(GrowingArray && aGrowingArray)
	{
		delete[] myArray;
		myArray = aGrowingArray.myArray;
		aGrowingArray.myArray = nullptr;
		myCurrentSize = aGrowingArray.myCurrentSize;
		aGrowingArray.myCurrentSize = 0;
		myMaxSize = aGrowingArray.myMaxSize;
		aGrowingArray.myMaxSize = 0;
		myUseSafeMode = aGrowingArray.myUseSafeMode;
		myIsInitialized = aGrowingArray.myIsInitialized;
		aGrowingArray.myIsInitialized = false;
		return *this;
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Init(SizeType aNrOfRecomendedItems, bool aUseSafeModeFlag)
	{
		assert(!myIsInitialized && "GrowingArray is already initialized");
		myCurrentSize = 0;
		myMaxSize = aNrOfRecomendedItems;
		myArray = new ObjectType[myMaxSize];
		myUseSafeMode = aUseSafeModeFlag;
		myIsInitialized = true;
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::ReInit(SizeType aNrOfRecomendedItems, bool aUseSafeModeFlag)
	{
		assert(myIsInitialized && "GrowingArray is not initialized");
		delete[] myArray;
		myArray = nullptr;
		myIsInitialized = false;
		Init(aNrOfRecomendedItems, aUseSafeModeFlag);
	}
	template<typename ObjectType, typename SizeType>
	inline ObjectType & GrowingArray<ObjectType, SizeType>::operator[](const SizeType & aIndex)
	{
		assert(myIsInitialized && "GrowingArray is not initialized");
		assert(aIndex >= 0 && aIndex < myCurrentSize && "Index out of bounds");
		return myArray[aIndex];
	}
	template<typename ObjectType, typename SizeType>
	inline const ObjectType & GrowingArray<ObjectType, SizeType>::operator[](const SizeType & aIndex) const
	{
		assert(myIsInitialized && "GrowingArray is not initialized");
		assert(aIndex >= 0 && aIndex < myCurrentSize && "Index out of bounds");
		return myArray[aIndex];
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Add(const ObjectType & aObject)
	{
		assert(myIsInitialized && "GrowingArray is not initialized");
		if (myCurrentSize + 1 > myMaxSize)
		{
			Reserve(myMaxSize * 2);
		}
		myArray[myCurrentSize] = aObject;
		++myCurrentSize;
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Insert(SizeType aIndex, const ObjectType & aObject)
	{
		assert(myIsInitialized && "GrowingArray is not initialized");
		assert(aIndex >= 0 && aIndex < myCurrentSize && "Index out of bounds");
		if (myCurrentSize + 1 > myMaxSize)
		{
			Reserve(myMaxSize * 2);
		}
		for (SizeType index = myCurrentSize; index > aIndex; --index)
		{
			myArray[index] = myArray[index - 1];
		}
		myArray[aIndex] = aObject;
		++myCurrentSize;
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::DeleteCyclic(const ObjectType & aObject)
	{
		assert(myIsInitialized && "GrowingArray is not initialized");
		DeleteCyclicAtIndex(Find(aObject));
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::DeleteCyclicAtIndex(SizeType aItemNumber)
	{
		assert(myIsInitialized && "GrowingArray is not initialized");
		assert(aItemNumber >= 0 && aItemNumber < myCurrentSize && "Index out of bounds");
		delete myArray[aItemNumber];
		RemoveCyclicAtIndex(aItemNumber);
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::RemoveCyclic(const ObjectType & aObject)
	{
		assert(myIsInitialized && "GrowingArray is not initialized");
		RemoveCyclicAtIndex(Find(aObject));
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::RemoveCyclicAtIndex(SizeType aItemNumber)
	{
		assert(myIsInitialized && "GrowingArray is not initialized");
		assert(aItemNumber >= 0 && aItemNumber < myCurrentSize && "Index out of bounds");
		myArray[aItemNumber] = myArray[myCurrentSize - 1];
		--myCurrentSize;
	}
	template<typename ObjectType, typename SizeType>
	inline SizeType GrowingArray<ObjectType, SizeType>::Find(const ObjectType & aObject)
	{
		assert(myIsInitialized && "GrowingArray is not initialized");
		for (SizeType index = 0; index < myCurrentSize; ++index)
		{
			if (myArray[index] == aObject)
			{
				return index;
			}
		}
		return FoundNone;
	}
	template<typename ObjectType, typename SizeType>
	inline ObjectType & GrowingArray<ObjectType, SizeType>::GetLast()
	{
		assert(myIsInitialized && "GrowingArray is not initialized");
		return myArray[myCurrentSize - 1];
	}
	template<typename ObjectType, typename SizeType>
	inline const ObjectType & GrowingArray<ObjectType, SizeType>::GetLast() const
	{
		assert(myIsInitialized && "GrowingArray is not initialized");
		return myArray[myCurrentSize - 1];
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::RemoveAll()
	{
		assert(myIsInitialized && "GrowingArray is not initialized");
		myCurrentSize = 0;
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::DeleteAll()
	{
		assert(myIsInitialized && "GrowingArray is not initialized");
		for (SizeType index = 0; index < myCurrentSize; ++index)
		{
			delete myArray[index];
		}
		myCurrentSize = 0;
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Optimize()
	{
		assert(myIsInitialized && "GrowingArray is not initialized");
		Reserve(myCurrentSize);
	}
	template<typename ObjectType, typename SizeType>
	inline SizeType GrowingArray<ObjectType, SizeType>::Size() const
	{
		return myCurrentSize;
	}
	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Reserve(SizeType aNewSize)
	{
		assert(myIsInitialized && "GrowingArray is not initialized");
		ObjectType* oldArray = myArray;
		myMaxSize = aNewSize;
		myArray = new ObjectType[myMaxSize];
		if (myUseSafeMode)
		{
			SizeType oldSize = myCurrentSize;
			myCurrentSize = 0;
			for (SizeType index = 0; index < oldSize && index < myMaxSize; ++index)
			{
				myArray[index] = oldArray[index];
				++myCurrentSize;
			}
		}
		else
		{
			if (myCurrentSize <= myMaxSize)
			{
				memcpy(myArray, oldArray, sizeof(ObjectType) * myCurrentSize);
			}
			else
			{
				memcpy(myArray, oldArray, sizeof(ObjectType) * myMaxSize);
				myCurrentSize = myMaxSize;
			}
		}
		delete[] oldArray;
	}

	template<typename ObjectType, typename SizeType>
	inline void GrowingArray<ObjectType, SizeType>::Resize(SizeType aNewSize)
	{
		assert(myIsInitialized && "GrowingArray is not initialized");
		int sizeMultiplier = 1;
		while (aNewSize > myMaxSize * sizeMultiplier)
		{
			sizeMultiplier *= 2;
		}
		if (sizeMultiplier > 1)
		{
			Reserve(myMaxSize * sizeMultiplier);
		}
		myCurrentSize = aNewSize;
	}
};