#pragma once
#include <cmath>

namespace CommonUtilities
{

	template <class T>
	class Vector3
	{
	public:
		T x;
		T y;
		T z;

		Vector3<T>();
		Vector3<T>(const T& aX, const T& aY, const T& aZ);
		Vector3<T>(const Vector3<T>& aVector) = default;
		Vector3<T>& operator=(const Vector3<T>& aVector3) = default;
		~Vector3<T>() = default;
		T LengthSqr() const;
		T Length() const;
		Vector3<T> GetNormalized() const;
		void Normalize();
		T Dot(const Vector3<T>& aVector) const;
		Vector3<T> Cross(const Vector3<T>& aVector) const;
	};

	//Returns the vector sum of aVector0 and aVector1
	template <class T>
	Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		T myX = aVector0.x + aVector1.x;
		T myY = aVector0.y + aVector1.y;
		T myZ = aVector0.z + aVector1.z;

		Vector3<T> vector3(myX, myY, myZ);

		return vector3;
	}


	//Returns the vector difference of aVector0 and aVector1
	template <class T>
	Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		T myX = aVector0.x - aVector1.x;
		T myY = aVector0.y - aVector1.y;
		T myZ = aVector0.z - aVector1.z;

		Vector3<T> vector3(myX, myY, myZ);

		return vector3;
	}


	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T>
	Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar)
	{
		T myX = aVector.x * aScalar;
		T myY = aVector.y * aScalar;
		T myZ = aVector.z * aScalar;

		Vector3<T> vector3(myX, myY, myZ);

		return vector3;
	}


	//Returns the vector aVector multiplied by the scalar aScalar
	template <class T>
	Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
	{
		T myX = aVector.x * aScalar;
		T myY = aVector.y * aScalar;
		T myZ = aVector.z * aScalar;

		Vector3<T> vector3(myX, myY, myZ);

		return vector3;
	}


	//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1/aScalar)
	template <class T>
	Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar)
	{
		T myX = aVector.x / aScalar;
		T myY = aVector.y / aScalar;
		T myZ = aVector.z / aScalar;

		Vector3<T> vector3(myX, myY, myZ);

		return vector3;
	}


	//Equivalent to setting aVector0 to (aVector0 + aVector1)
	template <class T>
	void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
		aVector0.z += aVector1.z;
	}


	//Equivalent to setting aVector0 to (aVector0 - aVector1)
	template <class T>
	void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
		aVector0.z -= aVector1.z;
	}


	//Equivalent to setting aVector to (aVector * aScalar)
	template <class T>
	void operator*=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
		aVector.z *= aScalar;
	}


	//Equivalent to setting aVector to (aVector / aScalar)
	template <class T>
	void operator/=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
		aVector.z /= aScalar;
	}


	template<class T>
	inline Vector3<T>::Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}


	template<class T>
	Vector3<T>::Vector3(const T & aX, const T & aY, const T & aZ)
	{
		x = aX;
		y = aY;
		z = aZ;
	}

	template<class T>
	T Vector3<T>::LengthSqr() const
	{
		return ((x*x) + (y*y) + (z*z));
	}


	template<class T>
	T Vector3<T>::Length() const
	{
		return sqrt((x*x) + (y*y) + (z*z));
	}


	template<class T>
	inline Vector3<T> Vector3<T>::GetNormalized() const
	{
		T length = Length();
		return Vector3<T>(x / length, y / length, z / length);
	}


	template<class T>
	inline void Vector3<T>::Normalize()
	{
		if (LengthSqr() <= static_cast<T>(0.0f))
		{
			return;
		}
		T temp = sqrt(x*x + y * y + z * z);
		x /= temp;
		y /= temp;
		z /= temp;
	}


	template<class T>
	inline T Vector3<T>::Dot(const Vector3<T>& aVector) const
	{
		T myX = x * aVector.x;
		T myY = y * aVector.y;
		T myZ = z * aVector.z;

		T dotProduct = myX + myY + myZ;

		return dotProduct;
	}


	template<class T>
	inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVector) const
	{
		T myX = aVector.x;
		T myY = aVector.y;
		T myZ = aVector.z;

		T returnX = (y) * (myZ)-(z) * (myY);
		T returnY = (z) * (myX)-(x) * (myZ);
		T returnZ = (x) * (myY)-(y) * (myX);

		Vector3<T> returnVector(returnX, returnY, returnZ);

		return returnVector;
	}

}