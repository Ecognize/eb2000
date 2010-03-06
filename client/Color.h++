#ifndef _EB2K_COLOR_CPP
#define _EB2K_COLOR_CPP

class Color
{
    public:
        Color(int r, int g, int b, int a = 0) : _r(r), _g(g), _b(b), _a(a) {  }

        unsigned r() { return _r; }
        unsigned g() { return _g; }
        unsigned b() { return _b; }
        unsigned a() { return _a; }

        unsigned int rgb2uint();

    private:
        unsigned short _r;
        unsigned short _g;
        unsigned short _b;
        unsigned short _a;
};

#endif
