// TODO: heading comment here
#ifndef _EB2K_SYSTEM_HPP_
#define _EB2K_SYSTEM_HPP_

// TODO: DoxyGen
class System
{
    public:
        /* Singletone access */
        static System& instance();
    private:
        /* Limiting access to instantiation & deinstantiation */
        System();
        ~System();
        /* Disallowing copy constructor & assignement operator */
        System(const System&) {}
        System& operator=(const System&) { return *this; }
        
    private:
        /* TODO: implementation-dependent data here */
};

#endif
