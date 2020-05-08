#include "../include/entity.hpp"

void Entity::set_health(int h) {
    health = h;
}

void Entity::set_damage(int d) {
    damage = d;
}

void Entity::set_position(pair<int, int> pos) {
    position = pos;
}

void Entity::set_vision(vector<pair<int, int> > vis) {
    vision = vis;
}

int Entity::get_damage() {
    return damage;
}

int Entity::get_health() {
    return health;
}

pair<int, int> Entity::get_position() {
    return position;
}

vector<pair<int, int> > Entity::get_vision() {
    return vision;
}