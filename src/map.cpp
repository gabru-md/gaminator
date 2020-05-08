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