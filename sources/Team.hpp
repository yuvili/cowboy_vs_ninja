#ifndef TEAM_HPP
#define TEAM_HPP
#include <vector>
#include <type_traits>
#include "Point.hpp"
#include "Character.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include "OldNinja.hpp"
#include "TrainedNinja.hpp"
#include "YoungNinja.hpp"
using namespace std;


namespace ariel{
class Team{
    protected:
        Character* leader;
        std::vector<Character*> members;

        void chooseLeader();
        Character* getTarget(Team* enemy);

    public:
        Team(Character* leader);
        ~Team(); // Destructor
        Team(const Team& other); // Copy constructor
        Team(Team&& other) noexcept; // Move constructor

        void add(Character*);
        void attack(Team*);
        int stillAlive();
        void print();
        Character getLeader();
};
};
#endif