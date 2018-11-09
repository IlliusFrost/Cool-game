#pragma once
#include <cmath>

namespace CommonUtilities
{

	template <class T>
	class Vector4
	{
	public:
		T x;
		T y;
		T z;
		T w;
		Vector4<T>();
		Vector4<T>(const T& aX, const T& aY, const T& aZ, const T& aW);
		Vector4<T>(const Vector4<T>& aVector) = default;
		Vector4<T>& operator=(const Vector4<T>& aVector4) = default;
		~Vector4<T>() = default;
		T LengthSqr() const;
		T Length() const;
		Vector4<T> GetNormalized() const;
		void Normalize();
		T Dot(const Vector4<T>& aVector) const;
	};


	//Returns the vector sum of aVector0 and aVector1
	template <class T>
	Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		T myX = aVector0.x + aVector1.x;
		T myY = aVector0.y + aVector1.y;
		T myZ = aVector0.z + aVector1.z;
		T myW = aVector0.w + aVector1.w;

		Vector4<T> vector4(myX, myY, myZ, myW);

		return vector4;
	}


	//Returns the vector difference of aVector0 and aVector1
	template <class T>
	Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		T myX = aVector0.x - aVector1.x;
		T myY = aVector0.y - aVector1.y;
		T myZ = aVector0.z - aVector1.z;
		T myW = aVector0.w - aVector1.w;

		Vector4<T> vector4(myX, myY, myZ, myW);

		return vector4;
	}


	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T>
	Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar)
	{
		T myX = aVector.x * aScalar;
		T myY = aVector.y * aScalar;
		T myZ = aVector.z * aScalar;
		T myW = aVector.w * aScalar;

		Vector4<T> vector4(myX, myY, myZ, myW);

		return vector4;
	}


	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T>
	Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector)
	{
		T myX = aVector.x * aScalar;
		T myY = aVector.y * aScalar;
		T myZ = aVector.z * aScalar;
		T myW = aVector.w * aScalar;

		Vector4<T> vector4(myX, myY, myZ, myW);

		return vector4;
	}


	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1/aScalar)
	template <class T>
	Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar)
	{
		T myX = aVector.x / aScalar;
		T myY = aVector.y / aScalar;
		T myZ = aVector.z / aScalar;
		T myW = aVector.w / aScalar;

		Vector4<T> vector4(myX, myY, myZ, myW);

		return vector4;
	}


	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T>
	void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
		aVector0.w += aVector1.w;
	}


	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T>
	void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
		aVector0.w -= aVector1.w;
	}


	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T>
	void operator*=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
		aVector.w *= aScalar;
	}


	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T>
	void operator/=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
		aVector.z /= aScalar;
		aVector.w /= aScalar;
	}


	template<class T>
	inline Vector4<T>::Vector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}


	template<class T>
	Vector4<T>::Vector4(const T & aX, const T & aY, const T & aZ, const T & aW)
	{
		x = aX;
		y = aY;
		z = aZ;
		w = aW;
	}


	template<class T>
	T Vector4<T>::LengthSqr() const
	{
		return ((x*x) + (y*y) + (z*z) + (w*w));
	}


	template<class T>
	T Vector4<T>::Length() const
	{
		return sqrt(((x*x) + (y*y) + (z*z) + (w*w)));
	}


	template<class T>
	inline Vector4<T> Vector4<T>::GetNormalized() const
	{
		T length = Length();
		return Vector4<T>(x / length, y / length, z / length, w / length);
	}


	template<class T>
	inline void Vector4<T>::Normalize()
	{
		if (LengthSqr() <= static_cast<T>(0.0f))
		{
			return;
		}

		T temp = sqrt(x*x + y * y + z * z + w * w);
		x /= temp;
		y /= temp;
		z /= temp;
		w /= temp;
	}


	template<class T>
	inline T Vector4<T>::Dot(const Vector4<T>& aVector) const
	{
		T myX = x * aVector.x;
		T myY = y * aVector.y;
		T myZ = z * aVector.z;
		T myW = w * aVector.w;

		T dotProduct = myX + myY + myZ + myW;

		return dotProduct;
	}

}
