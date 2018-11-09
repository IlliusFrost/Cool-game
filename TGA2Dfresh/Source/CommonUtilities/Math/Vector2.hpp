#pragma once
#include <cmath>
#include <assert.h>

namespace CommonUtilities
{

	template <class T>
	class Vector2
	{
	public:
		T x;
		T y;
		Vector2<T>();
		Vector2<T>(const T& aX, const T& aY);
		Vector2<T>(const Vector2<T>& aVector) = default;
		Vector2<T>& operator=(const Vector2<T>& aVector2) = default;
		~Vector2<T>() = default;
		T LengthSqr() const;
		T Length() const;
		Vector2<T> GetNormalized() const;
		void Normalize();
		T Dot(const Vector2<T>& aVector) const;
	};


	//Returns the vector sum of aVector0 and aVector1
	template <class T>
	Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		T myX = aVector0.x + aVector1.x;
		T myY = aVector0.y + aVector1.y;

		Vector2<T> vector2(myX, myY);

		return vector2;
	}


	//Returns the vector difference of aVector0 and aVector1
	template <class T>
	Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		T myX = aVector0.x - aVector1.x;
		T myY = aVector0.y - aVector1.y;

		Vector2<T> vector2(myX, myY);

		return vector2;
	}


	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T>
	Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar)
	{
		T myX = aVector.x * aScalar;
		T myY = aVector.y * aScalar;

		Vector2<T> vector2(myX, myY);

		return vector2;
	}


	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T>
	Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
	{
		T myX = aVector.x * aScalar;
		T myY = aVector.y * aScalar;

		Vector2<T> vector2(myX, myY);

		return vector2;
	}


	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1/aScalar)
	template <class T>
	Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar)
	{
		T myX = aVector.x / aScalar;
		T myY = aVector.y / aScalar;

		Vector2<T> vector2(myX, myY);

		return vector2;
	}


	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T>
	void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
	}


	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T>
	void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
	}


	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T>
	void operator*=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
	}


	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T>
	void operator/=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
	}


	template<class T>
	inline Vector2<T>::Vector2()
	{
		x = 0;
		y = 0;
	}


	template<class T>
	Vector2<T>::Vector2(const T & aX, const T & aY)
	{
		x = aX;
		y = aY;
	}


	template<class T>
	T Vector2<T>::LengthSqr() const
	{
		return ((x*x) + (y*y));
	}


	template<class T>
	T Vector2<T>::Length() const
	{
		return sqrt((x*x) + (y*y));
	}


	template<class T>
	inline Vector2<T> Vector2<T>::GetNormalized() const
	{
		T length = Length();
		return Vector2<T>(x / length, y / length);
	}


	template<class T>
	inline void Vector2<T>::Normalize()
	{
		if (LengthSqr() <= static_cast<T>(0.0f))
		{
			return;
		}
		T temp = sqrt(x*x + y * y);
		x /= temp;
		y /= temp;
	}


	template<class T>
	inline T Vector2<T>::Dot(const Vector2<T>& aVector) const
	{
		T myX = x * aVector.x;
		T myY = y * aVector.y;

		T dotProduct = myX + myY;

		return dotProduct;
	}

}