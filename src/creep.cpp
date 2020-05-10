#include "../include/creep.hpp"

int Creep::zenith_creeps_alive = 0;
int Creep::nadir_creeps_alive = 0;

Creep::Creep(Team _t) {
    team = _t;
    creep_id = generate_creep_id(); 
    logger = new Logger("CREEPS");
    set_damage(CREEP_BASE_DMG);
    set_vision(get_base_vision());
    set_position(get_base_position());
    set_type(get_creep_type());
    Map::get_world()->set_entity_pos(get_position(), cvt_type_to_id(get_type()));
    incr_alive(team);
}

void Creep::run() {
    this_thread::sleep_for(chrono::milliseconds(500));
    logger->debug("Running Creep Thread for " + get_team_name() + " Id: " + to_string(creep_id));
    while(no_enemy_in_sight()) {
        logger->warn("No enemy in sight!", {to_string(get_type())});
        move_forward();
        // if(has_reached_end()) {
        //     break;
        // }
    }
    logger->warn("Enemy in sight!", {get_team_name(), to_string(get_creep_id())});
    delete this;
}

Creep::~Creep() {
    logger->info("Creep Position: " + pos_to_str(), {get_team_name(), to_string(creep_id)});
    logger->warn("Creep died", {get_team_name(), to_string(creep_id)});
    decr_alive(team);
}


int Creep::generate_creep_id() {
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

int Creep::get_creep_id() {
    return creep_id;
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

set<pair<int, int> > Creep::get_base_vision() {
    switch(team) {
        case Team::ZENITH:
            return BASE_VISION_ZENITH;
        case Team::NADIR:
            return BASE_VISION_NADIR;
        default:
            return BASE_VISION_ZENITH;
    }
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

bool Creep::no_enemy_in_sight() {
    bool flag = true;
    vector<vector<int> > map = Map::get_world()->acquire_map();
    for(pair<int, int> vis: get_vision()) {
        if(map[vis.first][vis.second] == enemy_creep()) {
            // cout << vis.first << ", " << vis.second << endl;
            flag = false;
            break;
        }
    }
    Map::get_world()->release_map();
    return flag;
}

void Creep::move_forward() {
    Map::get_world()->acquire_method();
    vector<vector<int> > map = Map::get_world()->acquire_map();
    pair<int, int> creep_pos = get_position();
    int mv_dy;
    if(team == Team::ZENITH) {
        mv_dy = 1;
    } else {
        mv_dy = -1;
    }

    auto dx = {0, 1, -1};
    auto dy = {mv_dy};
    bool moved = false;
    for(int x: dx) {
        for(int y: dy) {
            if(is_valid(creep_pos, x, y, map)) {
                set_position({creep_pos.first + x, creep_pos.second + y});
                moved = true;
                break;
            }
        }
        if(moved)
            break;
    }
    Map::get_world()->release_map();
    // cout << "lol\n";
    // if entity couldn't move then check here -- TODO
    Map::get_world()->remove_entity_from_pos(creep_pos);
    Map::get_world()->set_entity_pos(get_position(), cvt_type_to_id(get_type()));
    logger->debug("Moved to " + pos_to_str(), {get_team_name(), to_string(get_creep_id())});
    logger->debug("Updating Vision", {get_team_name(), to_string(get_creep_id())});
    update_vision();
    
    Map::get_world()->release_method();
}

void Creep::update_vision() {
    int mv_dy;
    if(team == Team::ZENITH) {
        mv_dy = 1;
    } else {
        mv_dy = -1;
    }
    auto dx = {0, 2, -2};
    auto dy = {mv_dy};
    set<pair<int, int> > nv;
    pair<int, int> pos = get_position();
    for(auto x: dx) {
        for(auto y: dy) {
            if(is_in_bounds({pos.first + x, pos.second + y})) {
                nv.insert({pos.first + x, pos.second + y});
            }
        }
    }
    add_to_vision(nv);
    // logger->debug("Vision List Size: " + to_string(get_vision().size()), {get_team_name(), to_string(get_creep_id())});
}

bool Creep::has_reached_end() {
    if(team == Team::ZENITH) {
        if(get_position().second == MAP_LENGTH - 1)
            return false;
    } else {
        if(get_position().second == 0)
            return false;
    }
    return true;
}

void Creep::incr_alive(Team t) {
    switch(t) {
        case Team::ZENITH:
            Creep::zenith_creeps_alive++;
            break;
        case Team::NADIR:
            Creep::nadir_creeps_alive++;
            break;
    }
    game_logger->info("Alive Creeps Count: " + to_string(get_alive_count()), {"ALIVE"});
}

void Creep::decr_alive(Team t) {
    switch(t) {
        case Team::ZENITH:
            Creep::zenith_creeps_alive--;
            break;
        case Team::NADIR:
            Creep::nadir_creeps_alive--;
            break;
    }
    game_logger->info("Alive Creeps Count: " + to_string(get_alive_count()), {"DEAD"});
}

int Creep::get_alive_count() {
    return (
        get_alive_count(Team::ZENITH)
        +
        get_alive_count(Team::NADIR)
    );
}

int Creep::get_alive_count(Team t) {
    switch(t) {
        case Team::ZENITH:
            return zenith_creeps_alive;
        case Team::NADIR:
            return nadir_creeps_alive;
        default:
            return 0;
    }
}