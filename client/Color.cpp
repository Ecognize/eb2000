#include "Color.hpp"

/* Цветовые константы */
// elfy: ссылка берется от временного объекта, и как нам подсказывает Александреску
// ссылка удерживает временный объект от разрушения до тех пор, пока не выйдет из
// области видимости. В случае статических членов — пока программа не завершится.

// mix colors
Color & Color::operator &(const Color &c)
{
    /*if(this == c)       // check for self-assignment
        return *this;*/
    r() = (r() + c.r()) / 2;
    g() = (g() + c.g()) / 2;
    b() = (b() + c.b()) / 2;
    a() = (a() + c.a()) / 2;

    return (*this);
}

const Color& Color::White  = Color(255, 255, 255);
const Color& Color::Black  = Color(0,   0,   0);
const Color& Color::Red    = Color(255, 0,   0);
const Color& Color::Green  = Color(0,   255, 0);
const Color& Color::Blue   = Color(0,   0,   255);
const Color& Color::Yellow = Color(255, 255, 0);
