#include "shared/Vector.h++"

int main()
{
    Vector a;
    Vector b(4.5,6.0);
    Vector c(b);
    Vector d=c;
    std::cout << a << " " << b << " " << c << std::endl;
    b=a;
    std::cout << b << std::endl;
    a+=c;
    std::cout << a << std::endl;
    a-=c;
    std::cout << a << std::endl;
    c*=5.5;
    std::cout << c << std::endl;
    c/=5.5;
    std::cout << c << std::endl;
    std::cout << (a+c) << " " << (b-c) << std::endl;
    std::cout << (c*6) << " " << (c/6) << std::endl;
    c.normalize();
    std::cout << c << " len="<<c.length()<< " " << d << " len="<<d.length() << " mult=" << (d*c) << std::endl;
    return 0;
}