#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <vector>
#include <set>
#include <utility>
using namespace std;

/*

Layout of a 15x5 Map

- - - - - - - - - - - - - - -
U - - - - - - - - - - - - H L
U Z - - - - - - - - - - - N L
U G - - - - - - - - - - - - L
- - - - - - - - - - - - - - -

U = Zenith's Base
L = Nadir's Base
Z = Zenith Creep's Starting Position
N = Nadir Creep's starting Position
G = Zenith's Hero
H = Nadir's Hero

*/

// map dimensions
static const int MAP_LENGTH = 15; // cols
static const int MAP_WIDTH = 5; // rows

// identifiers
static const int ZENITH_BASE = 'U';
static const int NADIR_BASE = 'L';
static const int ZENITH_CREEP_IDENTIFIER = 'Z';
static const int NADIR_CREEP_IDENTIFIER = 'N';
static const int ZENITH_HERO_IDENTIFIER = 'G';
static const int NADIR_HERO_IDENTIFIER = 'H';
static const int BLANK_IDENTIFIER = 'B';

enum Team {
    ZENITH, // light force
    NADIR // Dark force
};

enum EntityType {
    BLANK,
    ZH, // Zenith's Hero
    NH, // Nadir's Hero
    ZC, // Zenith's Creep
    NC, // Nadir's Creep
    ZB, // Zenith's Base
    NB // Nadir's Base
};

static const set<pair<int, int> > get_base_zenith_vision();
static const set<pair<int, int> >get_base_nadir_vision();

// creep id counter
static int CREEP_ID_ZENITH = 0;
static int CREEP_ID_NADIR = 0;

// position in form of {row, col}
static const pair<int, int> CREEP_ZENITH_ST_POS = {2, 1};
static const pair<int, int> CREEP_NADIR_ST_POS = {2, 13};

// base damage for creep and hero
static const int CREEP_BASE_DMG = 10;
static const int HERO_BASE_DMG = 85;

// base health for creep and hero
static const int CREEP_BASE_HEALTH = 40;
static const int HERO_BASE_HEALTH = 500;

// creeps pool
// static const int MAX_CREEPS_POOL_SIZE = 5;
static const int MAX_CREEPS_POOL_SIZE = 1;

// base vision
static const set<pair<int, int> > BASE_VISION_ZENITH = get_base_zenith_vision();
static const set<pair<int, int> > BASE_VISION_NADIR = get_base_nadir_vision();

// hero and creep ranges
static const int MAX_CREEP_HIT_RANGE = 1;
static const int MAX_HERO_HIT_RANGE = 3;

// boundary for roaming
static const int ROAM_LEFT_BOUND = 1;
static const int ROAM_RIGHT_BOUND = MAP_LENGTH - 1;
static const int ROAM_TOP_BOUND = 0;
static const int ROAM_BOTTOM_BOUND = MAP_WIDTH - 1;

// vision methods
static const set<pair<int, int> > get_base_nadir_vision() {
    set<pair<int, int> > res;
    for(int i=0; i<4; i++) {
        for(int j=10; j<15; j++) {
            res.insert({i, j});
        }
    }
    return res;
}

static const set<pair<int, int> > get_base_zenith_vision() {
    set<pair<int, int> > res;
    for(int i=0; i<4; i++) {
        for(int j=0; j<5; j++) {
            res.insert({i, j});
        }
    }
    return res;
}
#endif