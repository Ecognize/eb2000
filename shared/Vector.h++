// TODO: Заголовочный комментарий сюда
#ifndef _EB2K_VECTOR_HPP
#define _EB2K_VECTOR_HPP

#include <vector>

/* Координатная система представлена двумя способами или «представлениями»:
    «экранное») стандартная декартовая система координат, нуль находится в левом нижнем углу,
        расстояния и положения измеряются пикселями
    «логическое») нормализированная декартова система координат, нуль находится в левом нижнем углу,
        расстояния и положения измеряются частями от 1
*/
    
// TODO: Кстати, какое стандартное соотношение w/h в игре?
// xela: определяется максимальным видеорежимом. 4:2.5 , 4:3, 10:8.
// elfy: а шо, тогда все растягивается? /r/ скрин с разными аспектами!

// TODO: DoxyGen
class Vector
{
    public:
        /* TODO: Математика & комментарии. Кто сделает — получит печеньку! */
        Vector();
        Vector(const Vector&);
        Vector(int x,int y);
        Vector(double x,double y);              // WARNING: перобразования типов же!
        Vector& operator=(const Vector&);       // Присваивание векторов
        Vector& operator+=(const Vector&);      // Присваивание суммы векторов
        Vector& operator-=(const Vector&);      // Присваивание разницы векторов
        Vector& operator*=(double);             // Увеличение вектора на число
        Vector& operator/=(double);             // Сокращение вектора на число
        Vector operator+(const Vector&) const;  // Сумма векторов
        Vector operator-(const Vector&) const;  // Разница векторов
        Vector operator/(double) const;         // Скалярное умножение на число, обратное аргументу
        Vector operator*(double) const;         // Скалярное умножение на число
        Vector operator*(const Vector&) const;  // Скалярное произведение векторов
        bool operator==(const Vector&) const;   // Равны ли вектора
        bool operator!=(const Vector&) const;   // Неравны ли вектора
        void length() const;                    // Длина вектора
        void normalize() const;                 // Нормализация вектора до единичной длины
        
        /* Методы в нижнем регистре возвращают экранные координаты */
        int x() const;
        int& x();
        int y() const;
        int &y();
        
        /* Методы в верхнем регистре возвращают логические координаты */
        double X() const;
        double& X();
        double Y() const;
        double& Y();
        
    private:
        /* Внутреннее представление данных, логическая система */
        std::vector<double> _data;
};

#endif