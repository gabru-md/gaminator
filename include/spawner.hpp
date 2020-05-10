#ifndef SPAWNER_H
#define SPAWNER_H

#include "creep.hpp"
#include "utils.hpp"
#include <vector>
using namespace std;


class SpawnService {
    private:
        Logger *logger;
        Logger *damage_logger;
        vector<Creep*> zenith_creeps;
        vector<Creep*> nadir_creeps;
        vector<thread> zenith_creeps_threads;
        vector<thread> nadir_creeps_threads;

    protected:
        void create_new_batch();
        void create_new_batch_specific(Team);
        void make_batch_threads();
        Creep* creep_at_pos(pair<int, int>, Team);
        Creep* zenith_creep_at_pos(pair<int, int>);
        Creep* nadir_creep_at_pos(pair<int, int>);

    public:
        SpawnService();
        ~SpawnService();
        void spawn();
        void damage_service();
        void run_damage_service();
        
};

#endif