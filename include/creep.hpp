#ifndef CREEP_H
#define CREEP_H

#include "logger.hpp"
#include "team.hpp"
#include "entity.hpp"

class Creep: protected Entity {
    private:
        Logger *logger;
        int creep_id;
        Team team;

        int get_creep_id();
        string get_team_name();
        vector<pair<int, int> > get_base_vision();
        pair<int, int> get_base_position();

    public:
        Creep(Team);
        ~Creep();
        void run();
};


#endif