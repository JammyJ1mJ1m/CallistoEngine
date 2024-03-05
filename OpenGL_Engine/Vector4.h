#pragma once
#include <iostream>
#include <exception>

class Vector4
{
	float _elements[4];
public:
	Vector4();
	Vector4(float x,float y, float z, float w);
	Vector4(float values[]);
	Vector4(const Vector4& copy);
	Vector4& operator=(const Vector4& copy);

public:

	float GetX() const { return _elements[0]; }
	float GetY() const { return _elements[1]; }
	float GetZ() const { return _elements[2]; }
	float GetW() const { return _elements[3]; }

	float GetR() const { return _elements[0]; }
	float GetG() const { return _elements[1]; }
	float GetB() const { return _elements[2]; }
	float GetA() const { return _elements[3]; }


	void Set(float x, float y, float z, float w);
	void Set(const Vector4& other);
	void Set(const float values[]);

	// inlines
	inline float dist2(float x, float y, float z) { return (float)(x * x) + (y * y) + (z * z); }

	inline float dist(float x, float y, float z) { return (float)sqrt(dist2(x, y, z)); }


	inline void divide(float val)
	{
		_elements[0] /= val;
		_elements[1] /= val;
		_elements[2] /= val;
		_elements[3] /= val;
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


	virtual ~Vector4();
};

