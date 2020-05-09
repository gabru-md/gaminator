#ifndef ENTITY_H
#define ENTITY_H

#include <utility>
#include <vector>
#include "team.hpp"
using namespace std;

class Entity {
    private:
        int health;
        int damage;
        int speed;
        int range;
        EntityType  type;
        pair<int, int> position;
        vector<pair<int, int> > vision;

    protected:
        void set_health(int);
        void set_damage(int);
        void set_position(pair<int, int>);
        void set_vision(vector<pair<int, int> >);
        void set_range(int);
        void set_type(EntityType);
        pair<int, int> get_base_vision();

    public:
        int get_health();
        int get_damage();
        pair<int, int> get_position();
        vector<pair<int, int> > get_vision();
        int get_range();
        bool has_no_enemy_in_vision();
        EntityType get_type();
        int cvt_type_to_id(EntityType);
};


#endif