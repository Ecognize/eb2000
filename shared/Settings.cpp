#include "Settings.hpp"

// main TODO: rewrite exceptions to use our ones

// constructor: open file
Settings::Settings(std::string file)
{
    sz = 0;

    fs.exceptions( std::fstream::failbit );
    filename = file;

    try {
        fs.open(filename.c_str(), std::fstream::in); } // open for reading
    catch (std::fstream::failure e)
    {
        std::cout << "can not open input file: " << filename << std::endl;
        exit(1);
    }

    std::cout << "file " << filename << " opened successfully" << std::endl;
}

// destructor: close file
Settings::~Settings()
{
    data.clear();

    if(fs.is_open())
        fs.close();
}

// trim whitespaces
std::string Settings::trim(std::string s)
{
    std::string whitespaces (" ");
    std::string::size_type start;
    std::string::size_type end;

    start = s.find_first_not_of(whitespaces);
    end   = s.find_last_not_of(whitespaces);

    return s.substr(start, end - start + 1);
}

// get settings count
unsigned int Settings::getCount()
{
    return sz;
}

// get copy of data
const std::map <std::string, std::string> Settings::getData()
{
    return data;
}

// parse file
void Settings::read()
{
    std::string key;
    std::string value;
    std::string buffer;
    std::string::size_type loc;
    std::string::size_type com;

    try {
        while(fs.good())
        {
            getline(fs, buffer);

            loc = buffer.find("=");             // basic delimiter
            com = buffer.find_first_of("#");    // comment sign

            if(loc != std::string::npos)        // set found
            {
                if(com == std::string::npos)    // no comments in this string
                {                               // just parse string
                    key   = trim(buffer.substr(0, loc));
                    value = trim(buffer.substr(loc + 1));
                    data.insert(std::pair <std::string, std::string> (key, value));
                    sz ++;
                }
                else                            // comment found
                {
                    if(com > loc)               // if it appended to the end of line
                    {
                        key   = trim(buffer.substr(0, loc));
                        value = trim(buffer.substr(loc + 1, com - loc - 1));
                        data.insert(std::pair <std::string, std::string> (key, value));
                        sz ++;
                    } // else just regular comment, ignore
                }
            } // else unrecognized string; TODO: error ?
        }
    }
    catch (std::fstream::failure) { }
}

// write file
void Settings::save()
{
    fs.clear();
    std::string line;

    try {
        if(fs.is_open())
            fs.close();

        fs.open(filename.c_str(), std::fstream::out); // overwrite
    }
    catch (std::fstream::failure e)
    {
        std::cout << "can not open file for writing: " << filename << std::endl;
        exit(1);
    }

    try {
        for(it = data.begin(); it != data.end(); it++)
        {
            line = it->first + " = " + it->second;
            fs << line;
            fs << std::endl;
        } } catch(std::fstream::failure e) { std::cout << "exception during writing";}

    try{
        fs.close();
    } catch (std::fstream::failure e) { std::cout << "can't close file"; }
}

// get val by key
std::string Settings::get(std::string key)
{
    it = data.find(key);

    if(it != data.end())
        return it->second;
    else return "NOT FOUND";
}

// erase val by key
void Settings::erase(std::string key)
{
    // find a key
    it = data.find(key);

    // just don't want to use exceptions here
    if(it != data.end()) // if key exists
        data.erase(it);
}

// set a new value or update existing
void Settings::set(std::string key, std::string value)
{
    // search
    it = data.find(key);

    if(it == data.end()) // if not found
        data.insert(std::pair<std::string, std::string> (key, value)); // just insert new
    else                 // otherwise update existing
    {
        data[key] = value;
    }
}

