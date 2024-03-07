#include "Vector3.h"

Vector3::Vector3()
{
	_elements[0] = 0.0f;
	_elements[1] = 0.0f;
	_elements[2] = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	Set(x, y, z);
}

Vector3::Vector3(float values[])
{
	Set(values);
}

Vector3::Vector3(const Vector3& copy)
{
	Set(copy);
}

Vector3& Vector3::operator=(const Vector3& copy)
{
	if (this == &copy) return *this;
	Set(copy);

	return *this;
}

void Vector3::Set(const float x, const float y, const float z)
{
	_elements[0] = x;
	_elements[1] = y;
	_elements[2] = z;

}

void Vector3::Set(const Vector3& other)
{
	_elements[0] = other.GetX();
	_elements[1] = other.GetY();
	_elements[2] = other.GetZ();

}

void Vector3::Set(const float values[])
{
	int length = sizeof(values);

	if (length < 2)
		throw std::exception("Vector must have at least 2 floats");
	else if (length > 4)
		throw std::exception("Vector must have no more than 4 floats");

	for (size_t i = 0; i < length; i++)
		_elements[i] = values[i];
}

Vector3::~Vector3()
{
}