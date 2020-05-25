/*
 * gameutils.hpp
 *
 *  Created on: 24-May-2020
 *      Author: gabru-md
 */

#ifndef INCLUDE_GAMEUTILS_HPP_
#define INCLUDE_GAMEUTILS_HPP_

#include "logger.hpp"
#include <vector>
#include <string>

using namespace std;

#define BCH BASE_CREEP_HEALTH
#define BCD BASE_CREEP_DAMAGE
#define ET EntityType

/*
 * 5 X 20 Map
 * . . . . . . . . . . . . . . . . . . . .
 * . . . . . . . . . . . . . . . . . . N .
 * . C . . . . . . . . . . . . . . . . C .
 * . Z . . . . . . . . . . . . . . . . . .
 * . . . . . . . . . . . . . . . . . . . .
 */


static Logger *creep_logger = new Logger("Creeps");
static Logger *game_logger = new Logger("Game");

enum EntityType {
	/*
	 * Zenith Creep = ZC
	 * Nadir Creep = NC
	 * Zenith Hero = ZH
	 * Nadir Hero = NH
	 */
	ZC, NC, ZH, NH, BLANK
};

static const int MAP_ROWS = 5;
static const int MAP_COLS = 20;

static const int MAP_LENGTH = MAP_COLS;
static const int MAP_WIDTH = MAP_ROWS;

static const int BASE_CREEP_HEALTH = 40;
static const int BASE_CREEP_DAMAGE = 12;

static int NC_ID = 0;
static int ZC_ID = 0;

static const pair<int, int> NC_START_POS = {2, MAP_COLS - 2};
static const pair<int, int> ZC_START_POS = {2, 1};
static const pair<int, int> NH_START_POS = {3, 1};
static const pair<int, int> ZH_START_POS = {1, MAP_COLS - 2};

static int generateCreepId(EntityType t) {
	switch(t) {
	case EntityType::NC:
		return NC_ID++;
	case EntityType::ZC:
		return ZC_ID++;
	default:
		return 0;
	}
}

static vector<int> getDx(EntityType t) {
	// for columns
	if(t == ET::NC || t == NH) {
		return {-1};
	}
	return {1};
}

static vector<int> getDy() {
	// for rows
	return {0, -1, 1};
}

static pair<vector<int>, vector<int>> getDxDy(EntityType t) {
	return {getDx(t), getDy()};
}

static string pairToString(pair<int, int> p) {
	return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

static pair<int, int> getStartingPosition(EntityType t) {
	switch(t) {
	case ET::NC:
		return NC_START_POS;
	case ET::ZC:
		return ZC_START_POS;
	case ET::NH:
		return NH_START_POS;
	case ET::ZH:
		return ZH_START_POS;
	default:
		return {0,0};
	}
}

#endif /* INCLUDE_GAMEUTILS_HPP_ */
