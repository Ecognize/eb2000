#include "shared/Settings.hpp"

int main()
{
    Settings set("settings");

    set.read();
    std::cout << "read " << set.getCount() << " settings. They are:" << std::endl;

    std::map <std::string, std::string> mydata = set.getData();

    for(std::map<std::string, std::string>::iterator iter = mydata.begin(); iter != mydata.end(); iter ++)
        std::cout << iter->first << " -> " << iter->second << std::endl;


    set.erase("set2");
    set.erase("setting");

    std::cout << std::endl << "after erasing: " << std::endl;

    mydata = set.getData();
    for(std::map<std::string, std::string>::iterator iter = mydata.begin(); iter != mydata.end(); iter ++)
        std::cout << iter->first << " -> " << iter->second << std::endl;

    set.set("music", "The Agonist");
    set.set("age", "21");

    std::cout << std::endl << "after updating: " << std::endl;

    mydata = set.getData();
    for(std::map<std::string, std::string>::iterator iter = mydata.begin(); iter != mydata.end(); iter ++)
        std::cout << iter->first << " -> " << iter->second << std::endl;

    set.save();

    return 0;
}

