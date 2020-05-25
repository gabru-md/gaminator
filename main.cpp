#include "include/map.hpp"
#include "include/creep.hpp"

int main() {
	Map *world = Map::getWorld();
	Creep *c = new Creep(ET::NC);
	thread creep_thread = c->spawn();
	creep_thread.join();
	Map::deleteWorld();
	return 0;
}
