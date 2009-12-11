#ifndef _EB2K_POINT_HPP_
#define _EB2K_POINT_HPP_

/* Отличается от вектора ограниченностью в пределах (0;0)—(1;1) или (0;0)—(w;h) */
/* TODO: что будет если к точке прибавить вектор и это ее выкинет за пределы экрана? */

class Point : public Vector //xela: ваще пока не вкуриваю назначение этих двух классов
{
    private:
        // почти заглушка
        class LogicalProxy;
        class ScreenProxy:
    public:
        /* Конструкторы проверяют ввод */
        Point(int,int);
        Point(double,double);
        Point(const Point&);
        explicit Point(const Vector&);
        /* Задача этих селектор-модификаторов — проверять ввод */
        LogicalProxy X();
        LogicalProxy Y();
        ScreenProxy x();
        ScreenProxy y();
        /* Временное решение — исключение, сообщающее о выходе за пределы экрана */
        class OutOfBounds {};
    private:
        /* Прячем методы Vector-а подальше */
        /* TODO: товарищам с МООП-ом — как еще лучше тут сделать и почему? */
        using Vector::x();
        using Vector::y();
        using Vector::X();
        using Vector::Y();
        /*  TODO: Прокси-класс для неконстантных методов. Тот, кто напишет, получит еще печеньку!
            Прокси должна проверять аргумент на выход за рамки окна при присваивании:
            (0;0)–(w;h) или (0;0)–(1;1) соответственно. Если аргумент «плохой» — кидаем исключение. */
};

#endif
