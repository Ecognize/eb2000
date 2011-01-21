#ifndef _EB2K_SETTINGS_HPP
#define _EB2K_SETTINGS_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>    // only for exit(); need to b removed
#include <string>
#include <map>

typedef std::map <std::string, std::string> setType;

class Settings
{
    public:
        /* construct & destruct */
        Settings();
        Settings(std::string file);
        ~Settings();

        /* fetching */
        std::string get(std::string key);             // get value by key

        /* setting and erasing */
        void set(std::string key, std::string value); // set new value; existing key will be overwritten
        void erase(std::string key);                  // erase value with specified key

        /* general purpose */
        void save();                                  // flush data to file
        void read();                                  // parse file
        unsigned int getCount();                      // get data count
        const setType getData();

    private:
        setType data;           // data container
        setType::iterator it;   // its iterator
        std::string filename;                               // filename storage
        std::fstream fs;                                    // stream descriptor
        unsigned int sz;                                    // number of settings

        std::string trim(std::string s);                    // trim whitespaces
};

#endif // _EB2K_SETTINGS_HPP
