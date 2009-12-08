#include "Vector.h++"

// TODO: commenting

/* Construction a.k.a. «easymode» */
Vector::Vector() : _data() // WARNING: stub, need to construct exactly two-element array
{ }

Vector::Vector(const Vector& p) : _data(p._data)
{ }

