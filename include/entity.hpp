#ifndef ENTITY_H
#define ENTITY_H

#include <utility>
#include <set>
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
        set<pair<int, int> > vision;

    protected:
        void set_health(int);
        void set_damage(int);
        void set_position(pair<int, int>);
        void set_vision(set<pair<int, int> >);
        void set_range(int);
        void set_type(EntityType);
        set<pair<int, int> > get_base_vision();

    public:
        int get_health();
        int get_damage();
        void update_health(int);
        void reduce_health(int);
        pair<int, int> get_position();
        set<pair<int, int> > get_vision();
        int get_range();
        bool has_no_enemy_in_vision();
        EntityType get_type();
        int cvt_type_to_id(EntityType);
        bool is_valid(pair<int, int>, int, int, vector<vector<int> >);
        bool is_in_bounds(pair<int, int>);
        string pos_to_str();
        void add_to_vision(set<pair<int, int>>);
};


#endif