#include "../include/spawner.hpp"

void SpawnService::create_new_batch_specific(Team t) {
    switch(t) {
        case Team::ZENITH:
            logger->debug("Creating new creeps batch", {"ZENITH"});
            zenith_creeps.resize(MAX_CREEPS_POOL_SIZE);
            for(int i=0;i<MAX_CREEPS_POOL_SIZE;i++) {
                zenith_creeps[i] = new Creep(Team::ZENITH);
            }
            break;
        case Team::NADIR:
            logger->debug("Creating new creeps batch", {"NADIR"});
            nadir_creeps.resize(MAX_CREEPS_POOL_SIZE);
            for(int i=0;i<MAX_CREEPS_POOL_SIZE;i++) {
                nadir_creeps[i] = new Creep(Team::NADIR);
            }
            break;
    }
}


void SpawnService::create_new_batch() {
    logger->debug("Creating new creeps batch", {"ZENITH", "NADIR"});
    create_new_batch_specific(Team::ZENITH);
    create_new_batch_specific(Team::NADIR);
}

void SpawnService::make_batch_threads() {
    logger-> debug("Making new batch of threads.");
    zenith_creeps_threads.resize(MAX_CREEPS_POOL_SIZE);
    nadir_creeps_threads.resize(MAX_CREEPS_POOL_SIZE);

    for(int i=0;i<MAX_CREEPS_POOL_SIZE;i++) {
        zenith_creeps_threads[i] = zenith_creeps[i]->spawn();
        nadir_creeps_threads[i] = nadir_creeps[i]->spawn();
    }

    for(int i=0;i<MAX_CREEPS_POOL_SIZE;i++) {
        zenith_creeps_threads[i].join();
        nadir_creeps_threads[i].join();
    }
}

SpawnService::SpawnService() {
    logger = new Logger("SPAWN-SERVICE");
    damage_logger = new Logger("DAMAGE");
    logger->debug("Starting Spawn Service!");
    damage_logger->info("Starting Damage Logger!");
}

void SpawnService::spawn() {
    create_new_batch();
    make_batch_threads();
}

void SpawnService::damage_service() {
    for(int i=0;i<MAX_CREEPS_POOL_SIZE;i++) {
        if(zenith_creeps[i]) {
            int creep_id = zenith_creeps[i]->get_creep_id();
            pair<int, int> enemy_pos = zenith_creeps[i]->get_enemy_in_sight();
            if(!is_pair_same(EMPTY_PAIR, enemy_pos)) {
                Creep* enemy_creep = creep_at_pos(enemy_pos, Team::NADIR);
                if(enemy_creep) {
                    damage_logger->info("Damage Given", {"ZENITH->NADIR", to_string(creep_id)});
                    // damage_logger->info("Creep Health: " + to_string(enemy_creep->get_creep_health()), {to_string(enemy_creep->get_creep_id())});
                    enemy_creep->damage_health(CREEP_BASE_DMG);
                    damage_logger->info("Creep Health: " + to_string(enemy_creep->get_creep_health()), {"NADIR", to_string(enemy_creep->get_creep_id())});
                }
            }
        }
        if(nadir_creeps[i]) {
            int creep_id = nadir_creeps[i]->get_creep_id();
            pair<int, int> enemy_pos = nadir_creeps[i]->get_enemy_in_sight();
            if(!is_pair_same(EMPTY_PAIR, enemy_pos)) {
                Creep* enemy_creep = creep_at_pos(enemy_pos, Team::ZENITH);
                if(enemy_creep) {
                    damage_logger->info("Damage Given", {"NADIR->ZENITH", to_string(creep_id)});
                    // damage_logger->info("Creep Health: " + to_string(enemy_creep->get_creep_health()), {to_string(enemy_creep->get_creep_id())});
                    enemy_creep->damage_health(CREEP_BASE_DMG);
                    damage_logger->info("Creep Health: " + to_string(enemy_creep->get_creep_health()), {"ZENITH" ,to_string(enemy_creep->get_creep_id())});
                }
            }
        }
    }
}

void SpawnService::run_damage_service() {
    damage_logger->info("Starting Damage Service Thread!");
    thread dmg_srvc(&SpawnService::damage_service, this);
    dmg_srvc.join();
    // damage_service();
}

Creep* SpawnService::creep_at_pos(pair<int, int> pos, Team t) {
    switch(t) {
        case Team::ZENITH:
            return zenith_creep_at_pos(pos);
        case Team::NADIR:
            return nadir_creep_at_pos(pos);
        default:
            return nadir_creep_at_pos(pos);
    }
}

Creep* SpawnService::zenith_creep_at_pos(pair<int, int> pos) {
    for(int i=0;i<MAX_CREEPS_POOL_SIZE;i++) {
        if(zenith_creeps[i] && is_pair_same(pos, zenith_creeps[i]->get_creep_position())) {
            return zenith_creeps[i];
        }
    }
    return NULL;
}

Creep* SpawnService::nadir_creep_at_pos(pair<int, int> pos) {
    for(int i=0;i<MAX_CREEPS_POOL_SIZE;i++) {
        if(nadir_creeps[i] && is_pair_same(pos, nadir_creeps[i]->get_creep_position())) {
            return nadir_creeps[i];
        }
    }
    return NULL;
}