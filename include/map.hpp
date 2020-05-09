#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <vector>
#include <mutex>
#include "logger.hpp"
#include "team.hpp"
#include "creep.hpp"
#include <thread>
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

        vector<Creep*> zenith_creeps;
        vector<Creep*> nadir_creeps;
        vector<thread> zenith_creeps_thread;
        vector<thread> nadir_creeps_thread;

        mutex map_lock;
        void spawn_creeps();

    public:
        Map();
        ~Map();
        static Map* get_world();
        static void delete_world();
        void set_entity_pos(pair<int, int>, int);
        vector<vector<int> > acquire_map();
        void release_map();
};

#endif