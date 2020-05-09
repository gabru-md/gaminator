#ifndef SPAWNER_H
#define SPAWNER_H

#include "creep.hpp"
#include <vector>
using namespace std;

class SpawnService {
    private:
        Logger *logger;
        vector<Creep*> zenith_creeps;
        vector<Creep*> nadir_creeps;
        vector<thread> zenith_creeps_threads;
        vector<thread> nadir_creeps_threads;

    protected:
        void create_new_batch();
        void create_new_batch_specific(Team);
        void make_batch_threads();

    public:
        SpawnService();
        ~SpawnService();
        void spawn();
        
};

#endif