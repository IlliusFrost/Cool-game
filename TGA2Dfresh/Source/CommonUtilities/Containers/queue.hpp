#pragma once
#include "DoublyLinkedList.hpp"
#include <assert.h>

namespace CommonUtilities
{
	template <class T>
	class Queue
	{
	public:
		//Skapar en tom k�
		Queue();
		Queue(const Queue<T>&) = delete;
		//Returnerar antal element i k�n
		int GetSize() const;
		//Returnerar elementet l�ngst fram i k�n. Kraschar med en assert om k�n �r
		//tom
		const T &GetFront() const;
		//Returnerar elementet l�ngst fram i k�n. Kraschar med en assert om k�n �r
		//tom
		T &GetFront();
		//L�gger in ett nytt element l�ngst bak i k�n
		void Enqueue(const T &aValue);
		//Tar bort elementet l�ngst fram i k�n och returnerar det. Kraschar med en
		//assert om k�n �r tom.
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