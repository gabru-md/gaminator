#include "include/map.hpp"
#include "include/logger.hpp"
#include "include/creep.hpp"

Map *Map::world = 0;

int main(void) {
    Map *world = Map::get_world();
    Creep *creep_1 = new Creep(Team::ZENITH);
    creep_1->run();
    Creep *creep_2 = new Creep(Team::NADIR);
    creep_2->run();
    Map::delete_world();
    return 0;
}