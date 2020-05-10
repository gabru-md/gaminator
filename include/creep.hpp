#ifndef CREEP_H
#define CREEP_H

#include "logger.hpp"
#include "team.hpp"
#include "entity.hpp"
#include "map.hpp"
#include <thread>

class Creep: protected Entity {
    private:
        Logger *logger;
        int creep_id;
        Team team;

        int generate_creep_id();
        EntityType get_creep_type();
        string get_team_name();
        set<pair<int, int> > get_base_vision();
        pair<int, int> get_base_position();
    
    protected:
        bool can_move_forward();
        int enemy_creep();
        void update_vision();

    public:
        Creep(Team);
        ~Creep();
        void run();
        bool no_enemy_in_sight();
        void move_forward();
        int get_creep_id();
        thread spawn() {
            return thread([=] { run(); });
        }
};


#endif