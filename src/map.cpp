#include "../include/map.hpp"


Map::Map() {
    logger = new Logger("WORLD");
    logger->debug("Creating Map: WORLD");

    auto now = chrono::system_clock::now();
    init_time = now;
    
    length = MAP_LENGTH; // cols
    width = MAP_WIDTH; // rows

    map.resize(width, vector<int>(length, BLANK_IDENTIFIER));
    logger->warn("Map Size " + to_string(map.size()) + ":" +to_string(map[0].size()));
    logger->debug("Map has length: " + to_string(length));
    logger->debug("Map has width: " + to_string(width));

}

Map::~Map() {
    logger->debug("Deleting Map: WORLD");
    delete logger;
}

void Map::delete_world() {
    delete world;
}

Map* Map::get_world() {
    if(!world) {
        world = new Map();
    }
    return world;
}

vector<vector<int> > Map::acquire_map() {
    logger->warn("Acquiring Map Lock", {"LOCK"});
    map_lock.lock();
    return map;
}

void Map::release_map() {
    try{
        logger->warn("Releasing the acquired Map Lock", {"LOCK"});
        map_lock.unlock();
    } catch(exception e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void Map::set_entity_pos(pair<int, int> pos, int id) {
    logger->warn("Setting position for Entity", {"POS", to_string(id)});
    map_lock.lock();
    map[pos.first][pos.second] = id;
    map_lock.unlock();
    logger->warn("Position Set Successful", {"POS", to_string(id)});
}

void Map::remove_entity_from_pos(pair<int, int> pos) {
    logger->warn("Acquiring Map", {"ENTITY", "RM"});
    map_lock.lock();
    map[pos.first][pos.second] = BLANK_IDENTIFIER;
    map_lock.unlock();    
    logger->warn("Releasing Map", {"ENTITY", "RM"});
}

void Map::acquire_method() {
    logger->info("Acquiring Method Lock", {"M-LOCK"});
    method_lock.lock();
}

void Map::release_method() {
    try{
        logger->warn("Releasing the acquired Map Lock", {"LOCK"});
        method_lock.unlock();
    } catch(exception e) {
        cerr << "Error: " << e.what() << endl;
    }
}