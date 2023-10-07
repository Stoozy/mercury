
#include <fstream>
#include <string>

#ifndef CONFIG_H
#define CONFIG_H

using std::string;
using std::ifstream;

class Config {
    private: 
        string m_config_path;
        ifstream m_file;

    public:
        Config(string path) : m_config_path(path){
            m_file = ifstream(path);
        };

        ~Config();

        bool exists();
        bool load();
};

#endif