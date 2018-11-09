#pragma once

namespace Tga2D
{
	template<class TYPE>
	struct SSimplePointerArray
	{
		SSimplePointerArray() :myData(nullptr), myNextCount(-1), mySize(0){}
		~SSimplePointerArray()
		{
			delete[] myData;
		}


		void Init(int aSize)
		{
			myNextCount = -1;
			mySize = aSize;	
			myData = new TYPE[aSize];
		}

		TYPE GetAt(int index)
		{
			return myData[index];
		}
		TYPE GetCurrent()
		{
			return myData[myNextCount];
		}
		TYPE *GetNext()
		{
			myNextCount++;
			return &myData[myNextCount];
		}

		void ResetCount()
		{
			myNextCount = -1;
		}

		int NextCount(){ return myNextCount; }
		int TotalCount(){ return mySize; }

		TYPE *myData;
		int myNextCount;
		int mySize;
	};
}