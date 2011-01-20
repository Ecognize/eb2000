#include "Vector.hpp"
#include <cmath>

// TODO: Комментирование

/* Конструирование a.k.a. «легкотня» */
Vector::Vector() : _data(2) // WARNING: заглушка, нужно ровно два элемента, забыл как пишется
{ }

Vector::Vector(const Vector& p) : _data(p._data)
{ }

Vector::Vector(double x,double y) : _data(2)
{
    _data[0]=x; // TODO initialize by list maybe?
    _data[1]=y;
}

/* Математика */

Vector& Vector::operator=(const Vector& p)
{
	_data=p._data;// TODO
	return (*this);
}

Vector& Vector::operator+=(const Vector& p)
{
	x()+=p.x();
	y()+=p.y();
	return (*this);
}

Vector& Vector::operator-=(const Vector& p)
{
	x()-=p.x();
	y()-=p.y();
	return (*this);
}    

Vector& Vector::operator*=(double p)
{
	x()*=p;
	y()*=p;
	return (*this);
}      

Vector& Vector::operator/=(double p)
{
	x()/=p;
	y()/=p;
	return (*this);
}          
 
Vector Vector::operator+(const Vector& p) const
{
  	return Vector(x()+p.x(),y()+p.y());
}
  
Vector Vector::operator-(const Vector& p) const
{
  	return Vector(x()-p.x(),y()-p.y());
}

Vector Vector::operator*(double p) const
{
	return Vector(x()*p,y()*p);	
}

Vector Vector::operator/(double p) const
{
	return ((*this)*(1.0/p));
}

int Vector::operator*(const Vector& p) const
{
	return x()*p.x()+y()*p.y();
}

void Vector::normalize()
{
    (*this)/=length();
}

double Vector::length() const
{
	return sqrt(x()*x()+y()*y());
}

bool Vector::operator==(const Vector& p) const { return (_data[0]==p._data[0])&&(_data[1]==p._data[1]); }
bool Vector::operator!=(const Vector& p) const { return !((*this)==p); }

/* Доступ к координатам */
double Vector::x() const { return _data[0]; }
double Vector::y() const { return _data[1]; }
// WARNING: временное решение
double& Vector::x() { return _data[0]; }
double& Vector::y() { return _data[1]; }

/* Вывод в stdout */
std::ostream& operator<<(std::ostream& str, const Vector& vec)
{
    str<<"("<<vec.x()<<";"<<vec.y()<<")";
}

