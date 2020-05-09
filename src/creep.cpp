#include "../include/creep.hpp"

Creep::Creep(Team _t) {
    team = _t;
    creep_id = get_creep_id(); 
    logger = new Logger("CREEPS");
    set_damage(CREEP_BASE_DMG);
    set_vision(get_base_vision());
    set_position(get_base_position());
    set_type(get_creep_type());

    // Map::get_world()->set_entity_pos(get_position(), cvt_type_to_id(get_type()));

    logger->debug("Base vision list size: " + to_string(get_vision().size()));
    logger->debug(get_team_name() + " Creep created with Id: " + to_string(creep_id));
}

void Creep::run() {
    this_thread::sleep_for(chrono::milliseconds(500));

    logger->debug("Running Creep Thread for " + get_team_name() + " Id: " + to_string(creep_id));
    delete this;
}

Creep::~Creep() {
    logger->debug("Creep died", {get_team_name(), to_string(creep_id)});
}


int Creep::get_creep_id() {
    switch(team) {
        case Team::ZENITH:
            return CREEP_ID_ZENITH++;
        case Team::NADIR:
            return CREEP_ID_NADIR++;
        default:
            return 0;
    }
}

string Creep::get_team_name() {
    switch(team) {
        case Team::ZENITH:
            return "Zenith";
        case Team::NADIR:
            return "Nadir";
        default:
            return "0";
    }
}

pair<int, int> Creep::get_base_position() {
    switch(team) {
        case Team::ZENITH:
            return CREEP_ZENITH_ST_POS;
        case Team::NADIR:
            return CREEP_NADIR_ST_POS;
        default:
            return CREEP_ZENITH_ST_POS;
    }
}

vector<pair<int, int> > Creep::get_base_vision() {
    switch(team) {
        case Team::ZENITH:
            return BASE_VISION_ZENITH;
        case Team::NADIR:
            return BASE_VISION_NADIR;
        default:
            return BASE_VISION_ZENITH;
    }
}

bool Creep::can_move_forward() {
    return has_no_enemy_in_vision();
}

int Creep::enemy_creep() {
    switch(team) {
        case Team::ZENITH:
            return NADIR_CREEP_IDENTIFIER;
        case Team::NADIR:
            return ZENITH_CREEP_IDENTIFIER;
        default:
            return NADIR_CREEP_IDENTIFIER;
    }
}

bool Creep::has_no_enemy_in_vision() {
    // vector<pair<int, int> > vision = get_vision();
    // vector<vector<int> > map = Map::get_world()->acquire_map();

    // for(auto pos: vision) {
    //     if(map[pos.first][pos.second] == enemy_creep()) {
    //         return false;
    //     }
    // }
    // Map::get_world()->release_map();
    return true;
}

EntityType Creep::get_creep_type() {
    switch(team) {
        case Team::ZENITH:
            return EntityType::ZC;
        case Team::NADIR:
            return EntityType::NC;
        default:
            return EntityType::ZC;
    }
}