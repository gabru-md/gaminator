#ifndef GAMEUTILS_H
#define GAMEUTILS_H


#include <set>
#include <vector>
using namespace std;

static bool is_pair_same(pair<int, int> p1, pair<int, int> p2) {
    return (
        (p1.first == p2.first)
        &&
        (p1.second == p2.second)
    );
}

static string pos_to_str(pair<int, int> position) {
    return "(" + to_string(position.first) + ", " +to_string(position.second) + ")";
}

#endif