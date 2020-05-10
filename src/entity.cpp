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

void Entity::set_vision(set<pair<int, int> > vis) {
    vision = vis;
}

void Entity::set_type(EntityType et) {
    type = et;
}

void Entity::set_range(int r) {
    range = r;
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

set<pair<int, int> > Entity::get_vision() {
    return vision;
}

int Entity::get_range() {
    return range;
}

EntityType Entity::get_type() {
    return type;
}

string Entity::pos_to_str() {
    return "(" + to_string(position.first) + ", " +to_string(position.second) + ")";
}

void Entity::add_to_vision(set<pair<int, int> > nv) {
    for(auto pos: nv) {
        vision.insert(pos);
    }
}

bool Entity::is_valid(pair<int, int> pos, int x, int y, vector<vector<int> > map) {
    int nx = pos.first + x;
    int ny = pos.second +y;
    return (
        ny >= ROAM_LEFT_BOUND && ny <= ROAM_RIGHT_BOUND
        &&
        nx >= ROAM_TOP_BOUND && nx <= ROAM_BOTTOM_BOUND
        &&
        map[nx][ny] == BLANK_IDENTIFIER
        );
}

int Entity::cvt_type_to_id(EntityType et) {
    switch(et) {
        case EntityType::ZB:
            return ZENITH_BASE;
        case EntityType::NB:
            return NADIR_BASE;
        case EntityType::BLANK:
            return BLANK_IDENTIFIER;
        case EntityType::ZC:
            return ZENITH_CREEP_IDENTIFIER;
        case EntityType::NC:
            return NADIR_CREEP_IDENTIFIER;
        case EntityType::ZH:
            return ZENITH_HERO_IDENTIFIER;
        case EntityType::NH:
            return NADIR_HERO_IDENTIFIER;
    }
}