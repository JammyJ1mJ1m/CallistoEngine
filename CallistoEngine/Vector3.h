#pragma once
#include <iostream>
#include <exception>

class Vector3
{
	float _elements[3];
public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(float values[]);
	Vector3(const Vector3& copy);
	Vector3& operator=(const Vector3& copy);

public:

	float GetX() const { return _elements[0]; }
	float GetY() const { return _elements[1]; }
	float GetZ() const { return _elements[2]; }


	float GetR() const { return _elements[0]; }
	float GetG() const { return _elements[1]; }
	float GetB() const { return _elements[2]; }



	void Set(float x, float y, float z);
	void Set(const Vector3& other);
	void Set(const float values[]);

	// inlines
	inline float dist2(float x, float y, float z) { return (float)(x * x) + (y * y) + (z * z); }

	inline float dist(float x, float y, float z) { return (float)sqrt(dist2(x, y, z)); }


	inline void divide(float val)
	{
		_elements[0] /= val;
		_elements[1] /= val;
		_elements[2] /= val;

	}

	inline float length()
	{
		return dist(_elements[0], _elements[1], _elements[2]);
	}

	inline void normalise()
	{
		float len = length();
		if (len != 0) divide(len);
	}


	virtual ~Vector3();
};
