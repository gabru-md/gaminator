#ifndef ENTITY_H
#define ENTITY_H

#include <utility>
#include <vector>
using namespace std;

class Entity {
    private:
        int health;
        int damage;
        int speed;
        pair<int, int> position;
        vector<pair<int, int> > vision;

    protected:
        void set_health(int);
        void set_damage(int);
        void set_position(pair<int, int>);
        void set_vision(vector<pair<int, int> >);
        pair<int, int> get_base_vision();

    public:
        int get_health();
        int get_damage();
        pair<int, int> get_position();
        vector<pair<int, int> > get_vision();

};


#endif