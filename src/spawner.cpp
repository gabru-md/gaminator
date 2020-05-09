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
    logger->debug("Starting Spawn Service!");
}

void SpawnService::spawn() {
    create_new_batch();
    make_batch_threads();
}