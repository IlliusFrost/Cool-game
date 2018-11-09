#pragma once
#include "DoublyLinkedList.hpp"
#include <assert.h>

namespace CommonUtilities
{
	template <class T>
	class Queue
	{
	public:
		//Skapar en tom kö
		Queue();
		Queue(const Queue<T>&) = delete;
		//Returnerar antal element i kön
		int GetSize() const;
		//Returnerar elementet längst fram i kön. Kraschar med en assert om kön är
		//tom
		const T &GetFront() const;
		//Returnerar elementet längst fram i kön. Kraschar med en assert om kön är
		//tom
		T &GetFront();
		//Lägger in ett nytt element längst bak i kön
		void Enqueue(const T &aValue);
		//Tar bort elementet längst fram i kön och returnerar det. Kraschar med en
		//assert om kön är tom.
		T Dequeue();

	private:
		DoublyLinkedList<T> myQueue;
		int mySize;
	};
	template<class T>
	inline Queue<T>::Queue()
	{
		mySize = 0;
	}
	template<class T>
	inline int Queue<T>::GetSize() const
	{
		return mySize;
	}
	template<class T>
	inline const T & Queue<T>::GetFront() const
	{
		assert(mySize != 0 && "Trying to get an empty queue!");
		return myQueue.GetLast()->GetValue();
	}
	template<class T>
	inline T & Queue<T>::GetFront()
	{
		assert(mySize != 0 && "Trying to get an empty queue!");
		return myQueue.GetLast()->GetValue();
	}
	template<class T>
	inline void Queue<T>::Enqueue(const T & aValue)
	{
		myQueue.InsertLast(aValue);
		++mySize;
	}
	template<class T>
	inline T Queue<T>::Dequeue()
	{
		assert(mySize != 0 && "Trying to dequeue an empty queue!");
		T retData = myQueue.GetFirst()->GetValue();
		myQueue.Remove(myQueue.GetFirst());
		--mySize;
		return retData;
	}
}