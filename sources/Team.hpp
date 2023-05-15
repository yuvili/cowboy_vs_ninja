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
    class Team {
        public:
            Character* leader;
            std::vector<Character*> members;

            Team(Character* leader);
            virtual ~Team(); // Destructor
            Team(const Team& other); // Copy constructor
            Team(Team&& other) noexcept; // Move constructor

            Team& operator=(const Team&);
            Team& operator=(Team&&) noexcept;

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

    class Team2 : public Team {
        public:
            Team2(Character* leader);

            void add(Character* member) override;
            int stillAlive();
            void attack(Team*);
            void print();

            std::vector<Character*> getTeam() const;
            Character* getLeader() const;
    };

    class SmartTeam : public Team {
        public:
            SmartTeam(Character* leader);

            void add(Character* member) override;
            int stillAlive();
            void attack(Team*);
            void print();

            std::vector<Character*> getTeam() const;
            Character* getLeader() const;
    };
};
#endif