#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <utility>
using namespace std;

/*

Layout of a 15x5 Map

- - - - - - - - - - - - - - -
Z - - - - - - - - - - - - T N
Z C - - - - - - - - - - - C N
Z T - - - - - - - - - - - - N
- - - - - - - - - - - - - - -

Z = Zenith's Base
N = Nadir's Base
T = Tanks' Starting Position
C = Creep's Starting Position

*/


enum Team {
    ZENITH, // light force
    NADIR // Dark force
};

static const vector<pair<int, int> > get_base_zenith_vision();
static const vector<pair<int, int> >get_base_nadir_vision();

// creep id counter
static int CREEP_ID_ZENITH = 0;
static int CREEP_ID_NADIR = 0;

// position in form of {row, col}
static const pair<int, int> CREEP_ZENITH_ST_POS = {5, 1};
static const pair<int, int> CREEP_NADIR_ST_POS = {5, 13};

// base damage for creep and hero
static const int CREEP_BASE_DMG = 10;
static const int HERO_BASE_DMG = 85;

// base health for creep and hero
static const int CREEP_BASE_HEALTH = 40;
static const int HERO_BASE_HEALTH = 500;

// creeps pool
static const int MAX_CREEPS_POOL_SIZE = 5;

// base vision
static const vector<pair<int, int> > BASE_VISION_ZENITH = get_base_zenith_vision();
static const vector<pair<int, int> > BASE_VISION_NADIR = get_base_nadir_vision();


// vision methods
static const vector<pair<int, int> > get_base_nadir_vision() {
    vector<pair<int, int> > res;
    for(int i=11; i<15; i++) {
        for(int j=0; j<5; j++) {
            res.push_back({i, j});
        }
    }
    return res;
}

static const vector<pair<int, int> > get_base_zenith_vision() {
    vector<pair<int, int> > res;
    for(int i=0; i<4; i++) {
        for(int j=0; j<5; j++) {
            res.push_back({i, j});
        }
    }
    return res;
}
#endif