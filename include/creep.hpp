/*
 * creep.hpp
 *
 *  Created on: 24-May-2020
 *      Author: gabru-md
 */

#ifndef INCLUDE_CREEP_HPP_
#define INCLUDE_CREEP_HPP_

#include "entity.hpp"

class Creep: public Entity {
private:
	int creepId;

public:
	Creep(EntityType);
	~Creep();

	// getters and setters
	int getCreepId();
	void setCreepId(int);

	// gameStrategy
	void gameStrategy();
};

#endif /* INCLUDE_CREEP_HPP_ */
