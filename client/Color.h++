#ifndef _EB2K_COLOR_CPP
#define _EB2K_COLOR_CPP

class Color
{
    public:
        Color(unsigned short r, unsigned short g, unsigned short b, unsigned short a = 0) : _r(r), _g(g), _b(b), _a(a) {  }
        Color() { }

        unsigned short r() const { return _r; }
        unsigned short g() const { return _g; }
        unsigned short b() const { return _b; }
        unsigned short a() const { return _a; }

        /* TODO: bound checks */
        unsigned short& r() { return _r; }
        unsigned short& g() { return _g; }
        unsigned short& b() { return _b; }
        unsigned short& a() { return _a; }

        /* Идеальные цветовые константы */

        static const Color& Black;
        static const Color& White;
        static const Color& Red;
        static const Color& Green;
        static const Color& Blue;
        // elfy: g++ может тут и без ссылок, но пусть пока будет так, безопаснее по-моему.

        // elfy: тут нужно написать хотя бы парочку операторов для цветов, смешивание, AND/OR итд, мне кажется

        Color & operator & (Color &c);
    private:
        unsigned short _r;
        unsigned short _g;
        unsigned short _b;
        unsigned short _a;
};

#endif
