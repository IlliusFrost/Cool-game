#pragma once
#include <vector>
#include <assert.h>

namespace CommonUtilities
{
	template <class T>
	inline void Swap(std::vector<T> &aVector, unsigned const int swapIndex1, unsigned const int swapIndex2)
	{
		assert(swapIndex1 <= aVector.size() && "First index out of range!");
		assert(swapIndex2 <= aVector.size() && "Second index out of range!");
		assert(swapIndex1 != swapIndex2 && "Indexes are equal!");

		T data = aVector[swapIndex1];

		aVector[swapIndex1] = aVector[swapIndex2];
		aVector[swapIndex2] = data;
	}

	template <class T>
	void SelectionSort(std::vector<T> &aVector)
	{
		assert(aVector.size() > 0 && "Trying to sort an empty vector!");
		int minPos;

		for (int i = 0; i < aVector.size() - 1; ++i)
		{
			minPos = i;

			for (int j = 0; j < aVector.size(); ++j)
			{
				if (aVector[j] < aVector)
				{
					minPos = j;
				}
			}

			if (minPos != i)
			{
				Swap(&aVector, minPos, i);
			}
		}
	}

	template <class T>
	void BubbleSort(std::vector<T> &aVector)
	{
		assert(aVector.size() > 0 && "Trying to sort an empty vector!");
		for (int i = 0; i < aVector.size() - 1; ++i)
		{
			for (int j = 0; j < aVector.size() - i - 1; ++j)
			{
				if (aVector[j + 1] < aVector[j])
				{
					Swap(&aVector, j + 1, j);
				}
			}
		}
	}

	template <class T>
	inline void RecursiveQuickSort(std::vector<T> &aVector, int left, int right)
	{
		int i = left;
		int j = right;
		int pivot = aVector[(left + right) / 2];

		while (i <= j)
		{
			while (aVector[i] < pivot)
			{
				++i;
			}

			while (pivot < aVector[j])
			{
				--j;
			}

			if (i <= j)
			{
				Swap(aVector, i, j);
				++i;
				--j;
			}
		}

		if (left < j || i < right)
		{
			RecursiveQuickSort(aVector, left, right);
		}
	}

	template <class T>
	void QuickSort(std::vector<T> &aVector)
	{
		assert(aVector.size() > 0 && "Trying to sort an empty vector!");

		int left = 0;
		int right = aVector.size() - 1;

		RecursiveQuickSort(aVector, left, right);
	}

	template <class T>
	inline void Merge(std::vector<T> &aVector, unsigned const int left, unsigned const int middle, unsigned const int right)
	{
		int i;
		int j;
		int k;
		int leftSize = middle - left + 1;
		int rightSize = right - middle;

		std::vector<T> leftSub;
		std::vector<T> rightSub;

		for (i = 0; i < leftSize; ++i)
		{
			leftSub.push_back(aVector[left + i]);
		}
		for (j = 0; j < rightSize; ++j)
		{
			rightSub.push_back(aVector[middle + 1 + j]);
		}

		i = 0;
		j = 0;
		k = left;
		while (i < leftSize && j < rightSize)
		{
			if (leftSub[i] <= rightSub[j])
			{
				aVector[k] = leftSub[i];
				++i;
			}
			else
			{
				aVector[k] = rightSub[i];
				++j;
			}
			++k;
		}

		while (i < leftSize)
		{
			aVector[k] = leftSub[i];
			++i;
			++k;
		}

		while (j < rightSize)
		{
			aVector[k] = rightSub[j];
			++j;
			++k;
		}
	}

	template <class T>
	inline void RecursiveMergeSort(std::vector<T> &aVector, unsigned const int left, unsigned const int right)
	{
		if (left < right)
		{
			int middle = left + (right - left) / 2;

			RecursiveMergeSort(aVector, left, middle);
			RecursiveMergeSort(aVector, middle + 1, right);

			Merge(aVector, left, middle, right);
		}
	}

	template <class T>
	void MergeSort(std::vector<T> &aVector)
	{
		assert(aVector.size() > 0 && "Trying to sort an empty vector!");

		int left = 0;
		int right = aVector.size() - 1;

		RecursiveMergeSort(aVector, left, right);
	}
}