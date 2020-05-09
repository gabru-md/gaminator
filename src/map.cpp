#include "../include/map.hpp"


Map::Map() {
    logger = new Logger("WORLD");
    logger->debug("Creating Map: WORLD");

    auto now = chrono::system_clock::now();
    init_time = now;
    
    length = LENGTH;
    width = WIDTH;
    logger->debug("Map has length: " + to_string(length));
    logger->debug("Map has width: " + to_string(width));

    zenith_creeps.resize(MAX_CREEPS_POOL_SIZE);
    nadir_creeps.resize(MAX_CREEPS_POOL_SIZE);
    zenith_creeps_thread.resize(MAX_CREEPS_POOL_SIZE);
    nadir_creeps_thread.resize(MAX_CREEPS_POOL_SIZE);

    spawn_creeps();
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

void Map::spawn_creeps() {
    logger->debug("Spawning Creeps for Zenith and Nadir.");
    for(int i=0;i<MAX_CREEPS_POOL_SIZE;i++) {
        zenith_creeps[i] = new Creep(Team::ZENITH);
        nadir_creeps[i] = new Creep(Team::NADIR);
    }

    for(int i=0;i<MAX_CREEPS_POOL_SIZE;i++) {
        zenith_creeps_thread[i] = zenith_creeps[i]->spawn();
        nadir_creeps_thread[i] = nadir_creeps[i]->spawn();

        zenith_creeps_thread[i].join();
        nadir_creeps_thread[i].join();
    }
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
}