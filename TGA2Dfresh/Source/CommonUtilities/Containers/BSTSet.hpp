#pragma once
#include <assert.h>

//Todo: make recursive
namespace CommonUtilities
{
	template <class T>
	struct TreeNode
	{
		T data;
		TreeNode<T>* leftChild = nullptr;
		TreeNode<T>* rightChild = nullptr;
	};

	template <class T>
	class BSTSet
	{
	public:
		BSTSet();
		~BSTSet();
		bool HasElement(const T& aValue);
		void Insert(const T &aValue);
		void Remove(const T &aValue);
		int GetSize() { return mySize; }

	private:
		TreeNode<T>* RemoveElement(const T aValue, TreeNode<T>* aNode);
		TreeNode<T>* myRoot;
		int mySize;
	};
}

template<class T>
inline CommonUtilities::BSTSet<T>::BSTSet() :
	myRoot(nullptr),
	mySize(0)
{
}

template<class T>
inline CommonUtilities::BSTSet<T>::~BSTSet()
{
}

template<class T>
inline bool CommonUtilities::BSTSet<T>::HasElement(const T & aValue)
{
	if (myRoot == nullptr)
	{
		return false;
	}

	TreeNode<T>* searcher = myRoot;
	while (searcher)
	{
		if ((!(searcher->data < aValue) && !(aValue < searcher->data)))
		{
			return true;
		}
		else if (aValue < searcher->data)
		{
			if (searcher->leftChild != nullptr)
			{
				searcher = searcher->leftChild;
			}
			else
			{
				return false;
			}
		}
		else if (searcher->data < aValue)
		{
			if (searcher->rightChild != nullptr)
			{
				searcher = searcher->rightChild;
			}
			else
			{
				return false;
			}
		}
	}
}

template<class T>
inline void CommonUtilities::BSTSet<T>::Insert(const T & aValue)
{
	if (mySize == 0)
	{
		myRoot = new TreeNode<T>();
		myRoot->data = aValue;
		++mySize;
	}
	else
	{
		TreeNode<T>* searcher = myRoot;

		while (searcher)
		{
			if ((!(searcher->data < aValue) && !(aValue < searcher->data)))
			{
				return;
			}
			else if (aValue < searcher->data)
			{
				if (searcher->leftChild != nullptr)
				{
					searcher = searcher->leftChild;
				}
				else
				{
					searcher->leftChild = new TreeNode<T>();
					searcher->leftChild->data = aValue;
					++mySize;
					return;
				}
			}
			else if (searcher->data < aValue)
			{
				if (searcher->rightChild != nullptr)
				{
					searcher = searcher->rightChild;
				}
				else
				{
					searcher->rightChild = new TreeNode<T>();
					searcher->rightChild->data = aValue;
					++mySize;
					return;
				}
			}
		}
	}
}

template<class T>
inline void CommonUtilities::BSTSet<T>::Remove(const T & aValue)
{
	RemoveElement(aValue, myRoot);
}

template<class T>
inline CommonUtilities::TreeNode<T> * CommonUtilities::BSTSet<T>::RemoveElement(const T aValue, CommonUtilities::TreeNode<T> * aNode)
{
	if (aNode == nullptr)
	{
		return aNode;
	}
	if (aValue < aNode->data)
	{
		aNode->leftChild = RemoveElement(aValue, aNode->leftChild);
	}
	else if (aValue > aNode->data)
	{
		aNode->rightChild = RemoveElement(aValue, aNode->rightChild);
	}
	else
	{
		if (aNode->leftChild == nullptr)
		{
			TreeNode<T>* temp = aNode->rightChild;
			aNode = nullptr;
			return temp;
		}
		else if (aNode->rightChild == nullptr)
		{
			TreeNode<T>* temp = aNode->leftChild;
			aNode = nullptr;
			return temp;
		}

		TreeNode<T>* temp = aNode->rightChild;

		while (temp->leftChild != nullptr)
		{
			temp = temp->leftChild;
		}

		aNode->data = temp->data;

		aNode->rightChild = RemoveElement(temp->data, aNode->rightChild);
	}
	return aNode;
}
