#include "Vector.h++"
#include "System.h++"
#include <cmath>

// TODO: Комментирование

/* Конструирование a.k.a. «легкотня» */
Vector::Vector() : _data() // WARNING: заглушка, нужно ровно два элемента, забыл как пишется
{ }

Vector::Vector(const Vector& p) : _data(p._data)
{ }

/* Математика */
void Vector::normalize()
{
    (*this)/=length();
}

bool operator==(const Vector& p) const { return (_data[0]==p._data[0])&&(_data[1]==p._data[1]); }
bool operator!=(const Vector& p) const { return !((*this)==p); }

/* Доступ к координатам */
int Vector::x() const { return _data[0]*System::playableWidth(); }
int Vector::y() const { return _data[1]*System::playableHeight(); }
double Vector::X() const { return _data[0]; }
double Vector::Y() const { return _data[1]; }
