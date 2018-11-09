#pragma once
#include "DoublyLinkedList.hpp"
#include <assert.h>

namespace CommonUtilities
{
	template <class T>
	class Stack
	{
	public:
		//Skapar en tom stack
		Stack();
		//Returnerar antal element i stacken
		int GetSize() const;
		//Returnerar det �versta elementet i stacken. Kraschar med en assert om
		//stacken �r tom.
		const T &GetTop() const;
		//Returnerar det �versta elementet i stacken. Kraschar med en assert om
		//stacken �r tom.
		T &GetTop();
		//L�gger in ett nytt element �verst p� stacken
		void Push(const T &aValue);
		//Tar bort det �versta elementet fr�n stacken och returnerar det. Kraschar
		//med en assert om stacken �r tom.
		T Pop();

	private:
		DoublyLinkedList<T> myStack;
		int mySize;
	};

	template<class T>
	inline Stack<T>::Stack()
	{
		mySize = 0;
	}

	template<class T>
	inline int Stack<T>::GetSize() const
	{
		return mySize;
	}

	template<class T>
	inline const T & Stack<T>::GetTop() const
	{
		assert(mySize != 0 && "Trying to get an empty stack!");
		return myStack.GetFirst()->GetValue();
	}
	template<class T>
	inline T & Stack<T>::GetTop()
	{
		assert(mySize != 0 && "Trying to get an empty stack!");
		return myStack.GetFirst()->GetValue();
	}
	template<class T>
	inline void Stack<T>::Push(const T & aValue)
	{
		myStack.InsertFirst(aValue);
		++mySize;
	}
	template<class T>
	inline T Stack<T>::Pop()
	{
		assert(mySize != 0 && "Trying to pop an empty stack!");
		T tempData = myStack.GetFirst()->GetValue();
		myStack.Remove(myStack.GetFirst());
		--mySize;
		return tempData;
	}
}