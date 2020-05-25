/*
 * map.hpp
 *
 *  Created on: 24-May-2020
 *      Author: gabru-md
 */

#ifndef INCLUDE_MAP_HPP_
#define INCLUDE_MAP_HPP_

#include "logger.hpp"
#include "gameutils.hpp"
#include <vector>
#include <mutex>
#include <map>
#include <vector>

class Map {
private:
	static Map* world;
	Logger* logger;
	int length;
	int width;
	vector<vector<EntityType>> gameMap;
	map<pair<int, int>, int> creepAtPosition;
	mutex map_lock;

public:
	Map();
	~Map();
	static Map* getWorld();
	static void deleteWorld();
	vector<vector<EntityType>> getMap();
	vector<vector<EntityType>> acquireMap();
	int getCreepAtPosition(pair<int, int>);
	void releaseMap();
	void addCreepAtPositionWithId(pair<int, int>, int);
	int removeCreepFromPosition(pair<int, int>);

};



#endif /* INCLUDE_MAP_HPP_ */
