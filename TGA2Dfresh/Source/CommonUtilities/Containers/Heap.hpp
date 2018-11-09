#pragma once
#include <vector>
#include <assert.h>

namespace CommonUtilities
{
	template <class T>
	class Heap
	{
	public:
		int GetSize() const; //returnerar antal element i heapen
		void Enqueue(const T &aElement); //lägger till elementet i heapen
		const T &GetTop() const; //returnerar det största elementet i heapen
		T Dequeue(); //tar bort det största elementet ur heapen och returnerar det

	private:
		std::vector<T> myHeap;

		void Swap(int aFirstIndex, int aSecondIndex);
		int GetParentIndex(int aIndex);
		int GetLChildIndex(int aIndex);
		int GetRChildIndex(int aIndex);
		bool GetIsValidIndex(int aIndex);
	};
	template<class T>
	inline void Heap<T>::Enqueue(const T & aElement)
	{
		myHeap.push_back(aElement);

		int index = myHeap.size() - 1;
		int parent = GetParentIndex(index);
		while (myHeap[parent] < myHeap[index] && index != 0)
		{
			Swap(index, parent);
			index = parent;
			parent = GetParentIndex(index);
		}
	}
	template<class T>
	inline const T & Heap<T>::GetTop() const
	{
		assert(myHeap.size() > 0 && "Heap is empty!");
		return myHeap[0];
	}
	template<class T>
	inline int Heap<T>::GetSize() const
	{
		return myHeap.size();
	}
	template<class T>
	inline T Heap<T>::Dequeue()
	{
		assert(myHeap.size() > 0 && "Heap is empty!");

		T data = myHeap[0];
		if (myHeap.size() == 1)
		{
			myHeap.pop_back();
			return data;
		}

		Swap(0, myHeap.size() - 1);
		myHeap.pop_back();

		int index = 0;
		int lChild = GetLChildIndex(index);
		int rChild = GetRChildIndex(index);
		while (index < myHeap.size() && (rChild < myHeap.size() || lChild < myHeap.size()))
		{
			if (GetIsValidIndex(rChild) && GetIsValidIndex(lChild))
			{
				if (myHeap[index] < myHeap[rChild] && myHeap[lChild] < myHeap[rChild])
				{
					Swap(index, rChild);
					index = rChild;
				}
				else if (myHeap[index] < myHeap[lChild] && myHeap[rChild] < myHeap[lChild])
				{
					Swap(index, lChild);
					index = lChild;
				}
			}
			else if (GetIsValidIndex(rChild) && !GetIsValidIndex(lChild))
			{
				if (myHeap[index] < myHeap[rChild])
				{
					Swap(index, rChild);
					index = rChild;
				}
				else
				{
					break;
				}
			}
			else if (GetIsValidIndex(lChild) && !GetIsValidIndex(rChild))
			{
				if (myHeap[index] < myHeap[lChild])
				{
					Swap(index, lChild);
					index = lChild;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
			lChild = GetLChildIndex(index);
			rChild = GetRChildIndex(index);
		}

		return data;
	}
	template<class T>
	inline void Heap<T>::Swap(int aFirstIndex, int aSecondIndex)
	{
		T data = myHeap[aSecondIndex];
		myHeap[aSecondIndex] = myHeap[aFirstIndex];
		myHeap[aFirstIndex] = data;
	}
	template<class T>
	inline int CommonUtilities::Heap<T>::GetParentIndex(int aIndex)
	{
		int retVal = (aIndex - 1) / 2;
		return retVal;
	}
	template<class T>
	inline int CommonUtilities::Heap<T>::GetLChildIndex(int aIndex)
	{
		int retVal = aIndex * 2 + 1;
		return retVal;
	}
	template<class T>
	inline int CommonUtilities::Heap<T>::GetRChildIndex(int aIndex)
	{
		int retVal = aIndex * 2 + 2;
		return retVal;
	}
	template<class T>
	inline bool CommonUtilities::Heap<T>::GetIsValidIndex(int aIndex)
	{
		if (aIndex < myHeap.size())
		{
			return true;
		}
		return false;
	}
}