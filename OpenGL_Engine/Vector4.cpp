#include "Vector4.h"

Vector4::Vector4()
{
	_elements[0] = 0.0f;
	_elements[1] = 0.0f;
	_elements[2] = 0.0f;
	_elements[3] = 0.0f;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	Set(x, y, z, w);
}

Vector4::Vector4(float values[])
{
	Set(values);
}

Vector4::Vector4(const Vector4& copy)
{
	Set(copy);
}

Vector4& Vector4::operator=(const Vector4& copy)
{
	if (this == &copy) return *this;
	Set(copy);

	return *this;
}

void Vector4::Set(const float x, const float y, const float z, const float w)
{
	_elements[0] = x;
	_elements[1] = y;
	_elements[2] = z;
	_elements[3] = w;
}

void Vector4::Set(const Vector4& other)
{
	_elements[0] = other.GetX();
	_elements[1] = other.GetY();
	_elements[2] = other.GetZ();
	_elements[3] = other.GetW();
}

void Vector4::Set(const float values[])
{
	int length = sizeof(values);

	if (length < 2)
		throw std::exception("Vector must have at least 2 floats");
	else if (length > 4)
		throw std::exception("Vector must have no more than 4 floats");

	for (size_t i = 0; i < length; i++)
		_elements[i] = values[i];
}

Vector4::~Vector4()
{
}
