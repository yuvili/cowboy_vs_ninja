#ifndef TEAM_HPP
#define TEAM_HPP
#include <vector>
#include <type_traits>
#include "Point.hpp"
#include "Character.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"
using namespace std;


namespace ariel{
class Team{
    private:
        Character* leader;
        std::vector<Character*> members;

    public:
        Team(Character* leader);
        virtual ~Team(); // Destructor
        Team(const Team& other); // Copy constructor
        Team(Team&& other) noexcept; // Move constructor

        virtual void add(Character*);
        void attack(Team*);
        int stillAlive();
        void print();

        void chooseLeader();
        Character* getTarget(Team* enemy);

        // Getters
        std::vector<Character*> getTeam() const;
        Character* getLeader() const;
};
};
#endif