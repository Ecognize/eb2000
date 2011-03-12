#ifndef __EB2K_POINT_HPP
#define __EB2K_POINT_HPP

class Point
{
    public:
        Point (unsigned int x, unsigned int y) : _x(x), _y(y) { }
        Point () : _x(0), _y(0) { }

        unsigned int x()          const { return _x; }
        unsigned int y()          const { return _y; }

        unsigned int &x()           { return _x; }
        unsigned int &y()           { return _y; }

    private:
        unsigned int _x;
        unsigned int _y;
};

#endif