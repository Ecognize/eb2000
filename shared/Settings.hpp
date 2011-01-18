#ifndef SETTINGS_HPP
#define SETTINGS_HPP

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
        void save();                            // flush vectors to file
        void read();                            // parse file
        unsigned int getCount();
        const std::map <std::string, std::string> getData();

    private:
        std::map <std::string, std::string> data;
        std::map <std::string, std::string>::iterator it;
        std::string filename;
        std::fstream fs;
        unsigned int sz;

        std::string trim(std::string s);         // trim whitespaces
};

#endif // SETTINGS_HPP
