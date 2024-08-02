#pragma once
#include <iostream>
#include <cmath>

template<typename T, int N>
class Vector
{
    T _elements[N];
public:
    Vector() {
        for (int i = 0; i < N; ++i)
            _elements[i] = T();
    }

    Vector(const T values[]) {
        for (int i = 0; i < N; ++i)
            _elements[i] = values[i];
    }

    Vector(const Vector& copy) {
        for (int i = 0; i < N; ++i)
            _elements[i] = copy._elements[i];
    }

    Vector(const std::initializer_list<T>& list) {
        int i = 0;
        for (const auto& element : list) {
            if (i >= N) break; 
            _elements[i++] = element;
        }
    }

    Vector& operator=(const Vector& copy) {
        if (this != &copy) {
            for (int i = 0; i < N; ++i)
                _elements[i] = copy._elements[i];
        }
        return *this;
    }

    T GetX() const { return _elements[0]; }
    T GetY() const { return _elements[1]; }
    T GetZ() const { return _elements[2]; }
    T GetW() const { return _elements[3]; }

    void SetX(T value) { _elements[0] = value; }
    void SetY(T value) { _elements[1] = value; }
    void SetZ(T value) { _elements[2] = value; }
    void SetW(T value) { _elements[3] = value; }

    T Length() const {
        T sumSquares = T();
        for (int i = 0; i < N; ++i)
            sumSquares += _elements[i] * _elements[i];
        return std::sqrt(sumSquares);
    }

    void Normalize() {
        T len = Length();
        if (len != T()) {
            for (int i = 0; i < N; ++i)
                _elements[i] /= len;
        }
    }


    virtual ~Vector() {}
};

typedef Vector<float, 2> Vector2f;
typedef Vector<float, 3> Vector3f;
typedef Vector<float, 4> Vector4f;

typedef Vector<double, 2> Vector2d;
typedef Vector<double, 3> Vector3d;
typedef Vector<double, 4> Vector4d;

typedef Vector<int, 2> Vector2i;
typedef Vector<int, 3> Vector3i;
typedef Vector<int, 4> Vector4i;