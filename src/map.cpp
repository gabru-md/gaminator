/*
 * map.cpp
 *
 *  Created on: 24-May-2020
 *      Author: gabru-md
 */

#include "../include/map.hpp"

Map *Map::world = 0;

Map::Map() {
	logger = new Logger("World");
	length = MAP_LENGTH; // columns
	width = MAP_WIDTH; // rows
	gameMap.resize(width, vector<EntityType>(length, EntityType::BLANK));
	logger->info("Map Rows: " + to_string(length));
	logger->info("Map Columns: " +to_string(width));
}

void Map::addCreepAtPositionWithId(pair<int, int> pos, int id) {
	if(creepAtPosition.find(pos) == creepAtPosition.end()) {
		creepAtPosition.insert({pos, id});
	}
}

int Map::removeCreepFromPosition(pair<int, int> pos) {
	if(creepAtPosition.find(pos) == creepAtPosition.end()) {
		return -1;
	}
	int creepId = creepAtPosition[pos];
	creepAtPosition.erase(pos);
	return creepId;
}

int Map::getCreepAtPosition(pair<int, int> pos) {
	if(creepAtPosition.find(pos) == creepAtPosition.end()) {
		return -1;
	}
	return creepAtPosition[pos];
}

Map::~Map() {
	logger->debug("Deleting Map: World");
	delete logger;
}

vector<vector<EntityType>> Map::getMap() {
	return acquireMap();
}

vector<vector<EntityType>> Map::acquireMap() {
	map_lock.lock();
	return gameMap;
}

void Map::releaseMap() {
	map_lock.unlock();
}

Map* Map::getWorld() {
	if(!world) {
		world = new Map();
	}
	return world;
}

void Map::deleteWorld() {
	delete world;
}
