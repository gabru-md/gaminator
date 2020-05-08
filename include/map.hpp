#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <vector>
#include "logger.hpp"
using namespace std;

#define LENGTH 15
#define WIDTH 5

class Map {
    private:
        static Map *world;
        Logger *logger;
        chrono::time_point<chrono::system_clock> init_time;
        vector<vector<int> > map;
        int length;
        int width;

    public:
        Map();
        ~Map();
        static Map* get_world();
        static void delete_world();
};

#endif