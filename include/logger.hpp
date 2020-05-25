/*
 * logger.hpp
 *
 *  Created on: 24-May-2020
 *      Author: gabru-md
 */

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
        enum level {DEBUG, WARN, INFO};
    
    private:
        string fmt(level, string);
        string fmt(string);
        string fmt(level, int);
        string fmt(level, double);

    public:
        Logger(string);
        ~Logger();
        void debug(string);
        void warn(string);
        void info(string);
        void log(string);
        void log(int);
        void log(double);
        void debug(string, vector<string>);
        void warn(string, vector<string>);
        void info(string, vector<string>);
};

#endif
