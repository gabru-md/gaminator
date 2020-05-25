/*
 * entity.cpp
 *
 *  Created on: 24-May-2020
 *      Author: gabru-md
 */


#include "../include/entity.hpp"

void Entity::moveForward() {
	if(isDead()) {
		return;
	}
	bool moved = false;
	vector<vector<ET>> map = Map::getWorld()->acquireMap();
	auto delta = getDxDy(type);
	auto dx = delta.first;
	auto dy = delta.second;
	auto currentPosition = getPosition();
	pair<int, int> newPosition = currentPosition;
	int f, s;
	f = currentPosition.first, s = currentPosition.second;
	for(int x: dx) {
		for(int y: dy) {
			int nf, ns;
			nf = f + y, ns = s + x;
			if(isSafeToMove({nf,ns}, map)) {
				newPosition = {nf, ns};
				moved = true;
				break;
			}
		}
		if(moved)
			break;
	}
	Map::getWorld()->removeCreepFromPosition(currentPosition);
	Map::getWorld()->releaseMap();
	game_logger->info("Entity moved forward to " + pairToString(newPosition));
	setPosition(newPosition);
	if(isAtEndPosition()) {
		setAlive(false);
	}
}

bool Entity::isAtEndPosition() {
	int colPosition =
			type == ET::NC ? ZC_START_POS.second : NC_START_POS.second;
	if(position.second == colPosition) {
		return true;
	}
	return false;
}

void Entity::reduceHealth(int h) {
	h = h < 0 ? h*-1 : h;
	health -= h;
	if(health <= 0) {
		setAlive(false);
	}
}

void Entity::increaseHealth(int h) {
	h = h < 0 ? h*-1 : h;
	health += h;
}

bool Entity::isInBounds(pair<int, int> pos) {
	int f = pos.first;
	int s = pos.second;
	return (f >= 0 && f <= MAP_ROWS && s >= 0 && s <= MAP_COLS);
}

bool Entity::isSafeToMove(pair<int, int> pos, vector<vector<ET>> map) {
	int f = pos.first;
	int s = pos.second;
	return (isInBounds(pos) && map[f][s] == EntityType::BLANK);
}

bool Entity::isEnemyInSight() {
	bool isEnemyHeroVisible = isEnemyHeroInSight();
	bool isEnemyCreepVisible = isEnemyCreepInSight();

	return isEnemyHeroVisible || isEnemyCreepVisible;
}

bool Entity::isEnemyCreepInSight() {
	bool yes = false;
	auto map = Map::getWorld()->acquireMap();
	for(auto pos: vision) {
		if(isInBounds(pos)) {
			int f = pos.first;
			int s = pos.second;
			if(map[f][s] == getEnemyCreepType()) {
				enemyCreepPosition = pos;
				yes = true;
				break;
			}
		}
	}
	Map::getWorld()->releaseMap();
	return yes;
}

bool Entity::isEnemyHeroInSight() {
	bool yes = false;
	auto map = Map::getWorld()->acquireMap();
	for(auto pos: vision) {
		int f = pos.first;
		int s = pos.second;
		if(map[f][s] == getEnemyHeroType()) {
			enemyHeroPosition = pos;
			yes = true;
			break;
		}
	}
	Map::getWorld()->releaseMap();
	return yes;
}

EntityType Entity::getEnemyCreepType() {
	if(type == EntityType::NC || type == EntityType::NH) {
		return EntityType::ZC;
	}
	return EntityType::NC;
}

EntityType Entity::getEnemyHeroType() {
	if(type == EntityType::NC || type == EntityType::NH) {
		return EntityType::ZH;
	}
	return EntityType::NH;
}

Entity::Entity(int h, int d, EntityType t) {
	setHealth(h);
	setDamage(d);
	setType(t);
	setAlive(true);
	setPosition(getStartingPosition(t));
}

Entity::~Entity() {}

int Entity::getDamage() {
	return damage;
}

int Entity::getId() {
	return id;
}

int Entity::getHealth() {
	return health;
}

EntityType Entity::getType() {
	return type;
}

pair<int, int> Entity::getPosition() {
	return position;
}

set<pair<int, int>> Entity::getVision() {
	return vision;
}

bool Entity::getAlive() {
	return alive;
}

bool Entity::isAlive() {
	return getAlive();
}

pair<int, int> Entity::getEnemyCreepPosition() {
	return enemyCreepPosition;
}

pair<int, int> Entity::getEnemyHeroPosition() {
	return enemyHeroPosition;
}

void Entity::setDamage(int d) {
	damage = d;
}

void Entity::setHealth(int h) {
	health = h;
}

void Entity::setType(EntityType t) {
	type = t;
}

void Entity::setId(int i) {
	id = i;
}

void Entity::setPosition(pair<int, int> pos) {
	position = pos;
	auto map = Map::getWorld()->acquireMap();
	int f = pos.first;
	int s = pos.second;
	map[f][s] = type;
	Map::getWorld()->addCreepAtPositionWithId(position, getId());
 	Map::getWorld()->releaseMap();
}

void Entity::setVision(set<pair<int, int>> vis) {
	vision = vis;
}

void Entity::setAlive(bool al) {
	alive = al;
}

bool Entity::isDead() {
	return !isAlive();
}

void Entity::run() {
	gameStrategy();
}
