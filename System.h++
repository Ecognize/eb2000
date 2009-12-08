// TODO: heading comment here
#ifndef _EB2K_SYSTEM_HPP_
#define _EB2K_SYSTEM_HPP_

#include "Vector.h++"
//#include "Sound.h++"
class Sound; // WARNING: stub

// TODO: DoxyGen
/*  This class emulates the procedure-based approach to lowest system calls
    while supporting the application's class hierarchy */
class System
{
    public:
        /* Sound playing routines */
        static void playSound(const Sound&);                // Plays the omnipositioned sound
        static void playSound(const Sound&,const Vector&);  // Plays the positioned sound
    private:
        /* Limiting access to instantiation & deinstantiation */
        System();
        ~System();
        /* Singletone access */
        static System& instance();
        /* Disallowing copy constructor & assignement operator */
        System(const System&) {}
        System& operator=(const System&) { return *this; }
        
    private:
        /* TODO: implementation-dependent data here */
};

#endif
