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

Vector& operator=(const Vector& p)
{
	_data=p._data;// TODO
	return _data;
}

Vector& operator+=(const Vector& p);
{
	x()+=p.x();
	y()+=p.y();
	return this;
}

Vector& operator-=(const Vector& p)
{
	x()-=p.x();
	y()-=p.y();
	return this;
}    

Vector& operator*=(double p);
{
	x()()*=p;
	y()()*=p;
	return this;
}      

Vector& operator/=(double p); 
{
	x()()/=p;
	y()()/=p;
	return this;
}          
 
Vector operator+(const Vector& p) const
{
  	return Vector(x()+p.x(),y()+p.y());
}
  
Vector operator-(const Vector& p) const
{
  	return Vector(x()-p.x(),y()-p.y());
}

Vector operator*(double p) const
{
	return Vector(x()*p,y()*p);	
}

Vector operator/(double p) const
{
	return ((*this)*(1.0/p));
}

int operator*(const Vector& p) const
{
	return x()*p.x()+y()*p.y();
}

void Vector::normalize()
{
    (*this)/=length();
}

double length() const
{
	return sqrt(x()()*x()()+y()()*y()());
}

bool operator==(const Vector& p) const { return (_data[0]==p._data[0])&&(_data[1]==p._data[1]); }
bool operator!=(const Vector& p) const { return !((*this)==p); }

/* Доступ к координатам */
int Vector::x() const { return _data[0]*System::playableWidth(); }
int Vector::y() const { return _data[1]*System::playableHeight(); }
double Vector::x()() const { return _data[0]; }
double Vector::y()() const { return _data[1]; }

/* Вывод в stdout */
std::ostream& operator<<(std::ostream& str, const Vector& vec)
{
    str<<"("<<vec.x()<<";"<<vec.y()<<")";
}

