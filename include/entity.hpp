/*
 * entity.hpp
 *
 *  Created on: 24-May-2020
 *      Author: gabru-md
 */

#ifndef INCLUDE_ENTITY_HPP_
#define INCLUDE_ENTITY_HPP_

#include "gameutils.hpp"
#include "map.hpp"
#include <utility>
#include <vector>
#include <set>
#include <thread>
using namespace std;

class Entity {
private:
	int health;
	int damage;
	bool alive;
	int id;
	EntityType type;
	pair<int, int> position;
	set<pair<int, int>> vision;

	pair<int, int> enemyCreepPosition;
	pair<int, int> enemyHeroPosition;

public:
	Entity(int, int, EntityType);
	~Entity();

	// getters and setters
	int getId();
	void setId(int);
	int getHealth();
	void setHealth(int);
	int getDamage();
	void setDamage(int);
	EntityType getType();
	void setType(EntityType);
	pair<int, int> getPosition();
	void setPosition(pair<int, int>);
	set<pair<int, int>> getVision();
	void setVision(set<pair<int, int>>);
	bool getAlive();
	void setAlive(bool);
	bool isAlive();
	bool isDead();
	pair<int, int> getEnemyCreepPosition();
	pair<int, int> getEnemyHeroPosition();

	// utility func
	void reduceHealth(int);
	void increaseHealth(int);
	bool isInBounds(pair<int, int>);
	bool isSafeToMove(pair<int, int>, vector<vector<ET>>);
	EntityType getEnemyCreepType();
	EntityType getEnemyHeroType();
	void moveForward();
	bool isAtEndPosition();

	// damage func
	bool isEnemyInSight();
	bool isEnemyCreepInSight();
	bool isEnemyHeroInSight();

	// virtual functions and spawn functionality
	virtual void gameStrategy() = 0;
	void run();
	thread spawn() {
		return thread([=] { run(); });
	}

};


#endif /* INCLUDE_ENTITY_HPP_ */
