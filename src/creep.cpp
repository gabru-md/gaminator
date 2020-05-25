/*
 * creep.cpp
 *
 *  Created on: 24-May-2020
 *      Author: gabru-md
 */

#include "../include/creep.hpp"

Creep::Creep(EntityType t) : Entity(BCH, BCD, t) {
	creepId = generateCreepId(t);
	setId(creepId);
	creep_logger->info("Spawned Creep with id: " + to_string(creepId));
}

int Creep::getCreepId() {
	return creepId;
}

void Creep::setCreepId(int id) {
	creepId = id;
}

void Creep::gameStrategy() {
	creep_logger->info("Creep strategy working!");
	while(isAlive()) {
		moveForward();
	}
	creep_logger->info("Creep Died!");
}
