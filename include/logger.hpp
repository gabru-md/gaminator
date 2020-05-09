#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>

using namespace std;

class Logger {
    private:
        string name;
        string log_file;
        ofstream stream;

        string def_loc = "logs/";

        bool open();
        bool close();
        
    protected:
        enum level {DEBUG, WARN};
    
    private:
        string fmt(level, string);
        string fmt(string);

    public:
        Logger(string);
        ~Logger();
        void debug(string);
        void debug(string, vector<string>);
        void warn(string, vector<string>);
        void warn(string);
};

#endif
