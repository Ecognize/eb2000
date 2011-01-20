#ifndef _EB2K_SETTINGS_HPP
#define _EB2K_SETTINGS_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>

class Settings
{
    public:
        /* construct & destruct */
        Settings(std::string file);
        ~Settings();

        /* fetching */
        std::string get(std::string key);       // get value by key

        /* setting and erasing */
        void set(std::string key, std::string value); // set new value; existing key will be overwritten
        void erase(std::string key);            // erase value with specified key

        /* general purpose */
        void save();                            // flush data to file
        void read();                            // parse file
        unsigned int getCount();
        const std::map <std::string, std::string> getData();

    private:
        std::map <std::string, std::string> data;           // data container
        std::map <std::string, std::string>::iterator it;   // its iterator
        std::string filename;                               // filename storage
        std::fstream fs;                                    // stream descriptor
        unsigned int sz;                                    // number of settings

        std::string trim(std::string s);                    // trim whitespaces
};

#endif // _EB2K_SETTINGS_HPP
