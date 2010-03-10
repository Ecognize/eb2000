#include "Color.h++"

/* Цветовые константы */
// elfy: ссылка берется от временного объекта, и как нам подсказывает Александреску
// ссылка удерживает временный объект от разрушения до тех пор, пока не выйдет из
// области видимости. В случае статических членов — пока программа не завершится.
const Color& Color::White=Color(255,255,255);
const Color& Color::Black=Color(0,0,0);
const Color& Color::Red=Color(255,0,0);
const Color& Color::Green=Color(0,255,0);
const Color& Color::Blue=Color(0,0,255);

// elfy: лолштоэто? Убрал нафиг, см. Color.h++
/*Color _color_black(0,0,0);
Color _color_white(255,255,255);
Color _color_red(255,0,0);
Color _color_green(0,255,0);
Color _color_blue(0,0,255);*/
