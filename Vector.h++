// TODO: heading comment here
#ifndef _EB2K_VECTOR_HPP
#define _EB2K_VECTOR_HPP

#include <vector>

/* The coordinate system is represented in two ways:
    "real") standard cartesian system with zero in leftmost bottom corner
        distances and positions measured in pixels
    "logical") normalized cartesian system with zero in leftmost bottom corner
        distances and positions measured in fractions of 1
*/
    
// TODO: What is the w/h aspect, by the way

// NB: Wanna argue this?


// TODO: DoxyGen
class Vector
{
    public:
        /* TODO: Math & comments. One who does this gets cookies! */
        Vector();
        Vector(const Vector&);
        Vector& operator=(const Vector&);
        Vector& operator+=(const Vector&);
        Vector& operator-=(const Vector&);
        Vector operator+(const Vector&) const;
        Vector operator-(const Vector&) const;
        
        /*  TODO: Proxy class around non-const members. One who does gets another cookie! 
            proxy must check the argument against the bounds of the window when assigning:
            (0;0)–(w;h) or (0;0)–(1;1) respectively. If argument is bad, throw exception */
        /* Lower-case methods return real coordinates */
        int x() const;
        int& x();
        int y() const;
        int &y();
        
        /* Upper case methods return logical coordinates */
        int X() const;
        int& X();
        int Y() const;
        int& Y();
        
    private:
        /* Internal data representation, in logical system */
        std::vector<double> _data;
};

#endif
