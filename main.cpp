#include "include/map.hpp"

#include <thread>

Map *Map::world = 0;

int main(void) {
    Map *world = Map::get_world();
    Map::delete_world();
    return 0;
}