#include "include/map.hpp"
#include "include/spawner.hpp"
#include <thread>

Map *Map::world = 0;

int main(void) {
    Map *world = Map::get_world();
    SpawnService *spawn_service = new SpawnService();
    spawn_service->spawn();
    spawn_service->run_damage_service();
    Map::delete_world();
    return 0;
}