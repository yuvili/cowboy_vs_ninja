#ifndef TEAM2_HPP
#define TEAM2_HPP
#include <string>
using namespace std;

#include "Team.hpp"
using namespace ariel;

class Team2 : protected Team {
    public:
        void add(Character*);
        void attack(Team*);
};
#endif