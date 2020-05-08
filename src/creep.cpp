#include "../include/creep.hpp"

Creep::Creep(Team _t) {
    logger = new Logger("CREEPS");
    team = _t;
    creep_id = get_creep_id(); 
    set_damage(CREEP_BASE_DMG);
    set_vision(get_base_vision());
    set_position(get_base_position());
    logger->debug("Base vision list size: " + to_string(get_vision().size()));
    logger->debug(get_team_name() + " Creep created with Id: " + to_string(creep_id));
}

void Creep::run() {
    logger->debug("Running Creep Thread for Id: " + to_string(creep_id));
    delete this;
}

Creep::~Creep() {
    logger->debug("Creep Id: " + to_string(creep_id) + " is dead");
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