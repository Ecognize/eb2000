#ifndef _EB2K_COLOR_CPP
#define _EB2K_COLOR_CPP

class Color
{
    public:
        Color(int r, int g, int b, int a = 0) : _r(r), _g(g), _b(b), _a(a) {  }

        unsigned r() const { return _r; }
        unsigned g() const { return _g; }
        unsigned b() const { return _b; }
        unsigned a() const { return _a; }

        /* Идеальные цветовые константы */

        static const Color& Black;
        static const Color& White;
        static const Color& Red;
        static const Color& Green;
        static const Color& Blue;
        // elfy: g++ может тут и без ссылок, но пусть пока будет так, безопаснее по-моему.

        // elfy: тут нужно написать хотя бы парочку операторов для цветов, смешивание, AND/OR итд, мне кажется
    private:
        unsigned short _r;
        unsigned short _g;
        unsigned short _b;
        unsigned short _a;
};

#endif
