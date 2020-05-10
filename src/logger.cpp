#include "../include/logger.hpp"
#include <algorithm>

string to_lower(string data) {
    transform(data.begin(), data.end(), data.begin(),
                [](unsigned char c){ return std::tolower(c); });
    return data;
}

Logger::Logger(string logger_name) {
    name = logger_name;
    log_file = to_lower(name) + ".log";
    open();
}

Logger::~Logger() {
    debug("Logger is exiting!");
    close();
}

void Logger::debug(string message) {
    if(!open()) {
        cerr << "Error logging debug statement!" << endl;
        return;
    }
    stream << fmt(level::DEBUG, message) << endl;
}

void Logger::debug(string message, vector<string> sym) {
    if(!open()) {
        cerr << "Error logging debug statement!" << endl;
        return;
    }
    string msg = "";
    for(string str: sym) {
        msg += "[" + str + "] ";
    }
    msg += message;
    stream << fmt(level::DEBUG, msg) << endl;
}

void Logger::warn(string message, vector<string> sym) {
    if(!open()) {
        cerr << "Error logging debug statement!" << endl;
        return;
    }
    string msg = "";
    for(string str: sym) {
        msg += "[" + str + "] ";
    }
    msg += message;
    stream << fmt(level::WARN, msg) << endl;
}

void Logger::warn(string message) {
    if(!open()) {
        cerr << "Error logging warning statement!" << endl;
        return;
    }
    stream << fmt(level::WARN, message) << endl;
}

void Logger::info(string message, vector<string> sym) {
    if(!open()) {
        cerr << "Error logging info statement!" << endl;
        return;
    }
    string msg = "";
    for(string str: sym) {
        msg += "[" + str + "] ";
    }
    msg += message;
    stream << fmt(level::INFO, msg) << endl;
}

void Logger::info(string message) {
    if(!open()) {
        cerr << "Error logging info statement!" << endl;
        return;
    }
    stream << fmt(level::INFO, message) << endl;
}

bool Logger::open() {
    if(name.length() == 0)
        return false;
    if(!stream.is_open()) {
        try {
            string log_file_path = def_loc + log_file;
            stream.open(log_file_path, ios_base::app | ios_base::in);
        } catch (exception& e) {
            cerr << "Error opening logger stream!" << endl;
            return false;
        }
    }
    return true;
}

bool Logger::close() {
    if(stream.is_open()) {
        try {
            stream.flush();
            stream.close();
        } catch(exception& e) {
            cerr << "Error closing logger stream!" << endl;
            return false;
        }
    }
    return true;
}

string chomp(string str) {
    int pos;
    if((pos=str.find('\n')) != string::npos)
            str.erase(pos);
    return str;
}

string Logger::fmt(string message) {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    string _fmt = chomp(ctime(&now_time));
    string res = "[" + _fmt + "] " + message;
    return res;
}

string Logger::fmt(level lvl, string message) {
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);
    string _fmt = chomp(ctime(&now_time));
    string _lvl;
    switch(lvl) {
        case level::WARN:
            _lvl = "WARN"; break;
        case level::DEBUG:
            _lvl = "DEBUG"; break;
        case level::INFO:
            _lvl = "INFO"; break;
    }
    string res = "[" + _fmt + "] [" +_lvl + "] " + "[" + name + "] " + message;
    return res;
}

