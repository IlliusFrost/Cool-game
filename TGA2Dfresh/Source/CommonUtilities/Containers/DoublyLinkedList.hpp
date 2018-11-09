#pragma once
#include <assert.h>

namespace CommonUtilities
{
	template<class T>
	class DoublyLinkedList;

	template <class T>
	class DoublyLinkedListNode
	{
	public:
		// Copy-konstruktorn och assignment-operatorn är borttagna, så att det enda
		// sättet att skapa en nod är genom att stoppa in ett värde i en lista.
		DoublyLinkedListNode<T>(const DoublyLinkedListNode<T> &) = delete;
		DoublyLinkedListNode<T>& operator=(const DoublyLinkedListNode<T> &) = delete;

		// Returnerar nodens värde
		const T &GetValue() const;
		T &GetValue();

		// Returnerar nästa nod i listan, eller nullptr om noden är sist i listan
		DoublyLinkedListNode<T> *GetNext() const;

		// Returnerar föregående nod i listan, eller nullptr om noden är först i
		// listan
		DoublyLinkedListNode<T> *GetPrevious() const;

	private:
		// Konstruktorn och destruktorn är privat, så att man inte kan skapa eller
		// ta bort noder utifrån. List-klassen är friend, så att den kan skapa
		// eller ta bort noder.
		friend class DoublyLinkedList<T>;
		DoublyLinkedListNode(const T& aValue);
		DoublyLinkedListNode();
		~DoublyLinkedListNode() {}

		T myData;

		DoublyLinkedListNode<T>* myNext;
		DoublyLinkedListNode<T>* myPrevious;
	};
	template <class T>
	class DoublyLinkedList
	{
	public:
		// Skapar en tom lista
		DoublyLinkedList();

		// Frigör allt minne som listan allokerat
		~DoublyLinkedList();

		// Returnerar antalet element i listan
		int GetSize() const;

		// Returnerar första noden i listan, eller nullptr om listan är tom
		DoublyLinkedListNode<T> *GetFirst();
		const DoublyLinkedListNode<T> *GetFirst() const;

		// Returnerar sista noden i listan, eller nullptr om listan är tom
		DoublyLinkedListNode<T> *GetLast();
		const DoublyLinkedListNode<T> *GetLast() const;

		// Skjuter in ett nytt element först i listan
		void InsertFirst(const T& aValue);

		// Skjuter in ett nytt element sist i listan
		void InsertLast(const T& aValue);

		// Skjuter in ett nytt element innan aNode
		void InsertBefore(DoublyLinkedListNode<T> *aNode, const T &aValue);

		// Skjuter in ett nytt element efter aNode
		void InsertAfter(DoublyLinkedListNode<T> *aNode, const T &aValue);

		// Plockar bort noden ur listan och frigör minne. (Det är ok att anta att
		// aNode är en nod i listan, och inte från en annan lista)
		void Remove(DoublyLinkedListNode<T> *aNode);

		// Hittar första elementet i listan som har ett visst värde. Jämförelsen
		// görs med operator==. Om inget element hittas returneras nullptr.
		DoublyLinkedListNode<T> *FindFirst(const T &aValue);

		// Hittar sista elementet i listan som har ett visst värde. Jämförelsen
		// görs med operator==. Om inget element hittas returneras nullptr.
		DoublyLinkedListNode<T> *FindLast(const T &aValue);

		// Plockar bort första elementet i listan som har ett visst värde. 
		// Jämförelsen görs med operator==. Om inget element hittas görs ingenting.
		// Returnerar true om ett element plockades bort, och false annars.
		bool RemoveFirst(const T &aValue);

		// Plockar bort sista elementet i listan som har ett visst värde.
		// Jämförelsen görs med operator==. Om inget element hittas görs ingenting.
		// Returnerar true om ett element plockades bort, och false annars.
		bool RemoveLast(const T &aValue);

	private:
		DoublyLinkedListNode<T>* myFirst;
		DoublyLinkedListNode<T>* myLast;
		int mySize;
	};

	template<class T>
	inline const T & DoublyLinkedListNode<T>::GetValue() const
	{
		return myData;
	}
	template<class T>
	inline T & DoublyLinkedListNode<T>::GetValue()
	{
		return myData;
	}
	template<class T>
	inline DoublyLinkedListNode<T>* DoublyLinkedListNode<T>::GetNext() const
	{
		if (myNext != nullptr)
		{
			return myNext;
		}
		return nullptr;
	}
	template<class T>
	inline DoublyLinkedListNode<T>* DoublyLinkedListNode<T>::GetPrevious() const
	{
		if (myPrevious != nullptr)
		{
			return myPrevious;
		}
		return nullptr;
	}
	template<class T>
	inline DoublyLinkedListNode<T>::DoublyLinkedListNode(const T & aValue)
	{
		myData = aValue;
		myNext = nullptr;
		myPrevious = nullptr;
	}
	template<class T>
	inline DoublyLinkedListNode<T>::DoublyLinkedListNode()
	{
		myNext = nullptr;
		myPrevious = nullptr;
	}
	template<class T>
	inline CommonUtilities::DoublyLinkedList<T>::DoublyLinkedList()
	{
		myFirst = nullptr;
		myLast = nullptr;
		mySize = 0;
	}

	template<class T>
	inline CommonUtilities::DoublyLinkedList<T>::~DoublyLinkedList()
	{
		while (myFirst != nullptr)
		{
			Remove(myFirst);
		}
	}

	template<class T>
	inline int CommonUtilities::DoublyLinkedList<T>::GetSize() const
	{
		return mySize;
	}

	template<class T>
	inline CommonUtilities::DoublyLinkedListNode<T>* CommonUtilities::DoublyLinkedList<T>::GetFirst()
	{
		return myFirst;
	}

	template<class T>
	inline const CommonUtilities::DoublyLinkedListNode<T>* CommonUtilities::DoublyLinkedList<T>::GetFirst() const
	{
		return myFirst;
	}

	template<class T>
	inline CommonUtilities::DoublyLinkedListNode<T>* CommonUtilities::DoublyLinkedList<T>::GetLast()
	{
		return myLast;
	}

	template<class T>
	inline const CommonUtilities::DoublyLinkedListNode<T>* CommonUtilities::DoublyLinkedList<T>::GetLast() const
	{
		return myLast;
	}

	template<class T>
	inline void CommonUtilities::DoublyLinkedList<T>::InsertFirst(const T & aValue)
	{
		DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(aValue);
		if (mySize != 0)
		{
			myFirst->myPrevious = newNode;
			newNode->myNext = myFirst;
			myFirst = newNode;
		}
		else
		{
			myFirst = newNode;
			myLast = newNode;
		}
		++mySize;
	}

	template<class T>
	inline void CommonUtilities::DoublyLinkedList<T>::InsertLast(const T & aValue)
	{
		DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(aValue);
		if (mySize != 0)
		{
			myLast->myNext = newNode;
			newNode->myPrevious = myLast;
			myLast = newNode;
		}
		else
		{
			myFirst = newNode;
			myLast = newNode;
		}
		++mySize;
	}

	template<class T>
	inline void CommonUtilities::DoublyLinkedList<T>::InsertBefore(DoublyLinkedListNode<T>* aNode, const T & aValue)
	{
		assert(aNode != nullptr && "This node is a nullptr! Can't insert value!");

		DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(aValue);
		newNode->myNext = aNode;
		if (aNode->myPrevious != nullptr)
		{
			newNode->myPrevious = aNode->myPrevious;
			aNode->myPrevious->myNext = newNode;
		}
		else
		{
			myFirst = newNode;
		}
		aNode->myPrevious = newNode;
		++mySize;
	}

	template<class T>
	inline void CommonUtilities::DoublyLinkedList<T>::InsertAfter(DoublyLinkedListNode<T>* aNode, const T & aValue)
	{
		assert(aNode != nullptr && "This node is a nullptr! Can't insert value!");

		DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(aValue);
		newNode->myPrevious = aNode;
		if (aNode->myNext != nullptr)
		{
			newNode->myNext = aNode->myNext;
			aNode->myNext->myPrevious = newNode;
		}
		else
		{
			myLast = newNode;
		}
		aNode->myNext = newNode;
		++mySize;
	}

	template<class T>
	inline void CommonUtilities::DoublyLinkedList<T>::Remove(DoublyLinkedListNode<T>* aNode)
	{
		assert(aNode != nullptr && "This node is a nullptr! Can't remove!");
		assert(myFirst && "myFirst was nullptr");

		if (aNode == myFirst)
		{
			if (myFirst->myNext != nullptr)
			{
				myFirst = myFirst->myNext;
				delete myFirst->myPrevious;
				myFirst->myPrevious = nullptr;
			}
			else
			{
				delete myFirst;
				myFirst = nullptr;
				myLast = nullptr;
			}
		}
		else if (aNode == myLast)
		{
			if (myLast->GetPrevious() != nullptr)
			{
				myLast = myLast->GetPrevious();
				delete myLast->myNext;
				myLast->myNext = nullptr;
			}
			else
			{
				delete myLast;
				myLast = nullptr;
				myFirst = nullptr;
			}
		}
		else
		{
			aNode->myNext->myPrevious = aNode->myPrevious;
			aNode->myPrevious->myNext = aNode->myNext;
			delete aNode;
			aNode = nullptr;
		}
		if (mySize > 0)
		{
			--mySize;
		}
	}

	template<class T>
	inline CommonUtilities::DoublyLinkedListNode<T>* CommonUtilities::DoublyLinkedList<T>::FindFirst(const T & aValue)
	{
		DoublyLinkedListNode<T>* node = myFirst;
		while (true)
		{
			if (node == nullptr || node->myData == aValue)
			{
				return node;
			}
			node = node->myNext;
		}
	}

	template<class T>
	inline CommonUtilities::DoublyLinkedListNode<T>* CommonUtilities::DoublyLinkedList<T>::FindLast(const T & aValue)
	{
		DoublyLinkedListNode<T>* node = myLast;
		while (true)
		{
			if (node == nullptr || node->myData == aValue)
			{
				return node;
			}
			node = node->myPrevious;
		}
	}

	template<class T>
	inline bool CommonUtilities::DoublyLinkedList<T>::RemoveFirst(const T & aValue)
	{
		if (FindFirst(aValue))
		{
			Remove(FindFirst(aValue));
			return true;
		}
		else
		{
			return false;
		}
	}

	template<class T>
	inline bool CommonUtilities::DoublyLinkedList<T>::RemoveLast(const T & aValue)
	{
		if (FindLast(aValue))
		{
			Remove(FindLast(aValue));
			return true;
		}
		else
		{
			return false;
		}
	}
}