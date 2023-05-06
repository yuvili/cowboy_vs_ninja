#include <string>
#include <stdexcept>
#include <typeinfo>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

#include "Team.hpp"

namespace ariel {
    Team::Team(Character* leader) : leader(leader), members(0)
    {
        members.push_back(leader);
        leader->setInTeam(true);
    }

    Team::~Team(){} // Destructor

    void Team::add(Character* member){
        if(members.size() >= 10){
            throw std::runtime_error("Max characters in team excided.");
        }
        if(member->inTeam){
            throw std::runtime_error(member->getName() + " is already in a team.");
        }
        
        members.push_back(member);
        member->setInTeam(true);
    }

    void Team::attack(Team* enemy){
        if(enemy->stillAlive() <= 0 || this->stillAlive() <= 0) {
            return;
        }

        if (!this->leader->isAlive()) {
            chooseLeader();
        }

        Character* target = getTarget(enemy);

        for(size_t i = 0; i < members.size(); i++) {
            if(enemy->stillAlive() <= 0 || this->stillAlive() <= 0) {
                break;
            }

            if(!target->isAlive()) {
                target = getTarget(enemy);
            }

            Cowboy* cb = dynamic_cast<Cowboy*>(members.at(i));

            if(cb != nullptr && cb->isAlive()) {
                if(cb->hasBullets()) {
                    cb->shoot(target);
                }
                else {
                    cb->reload();
                }
            }
        }

        for(size_t i = 0; i < members.size(); i++) {
            if(enemy->stillAlive() <= 0 || this->stillAlive() <= 0) {
                break;
            }

            if(!target->isAlive()) {
                target = getTarget(enemy);
            }

            Ninja* ninja = dynamic_cast<Ninja*>(members.at(i));
            
            if(ninja != nullptr && ninja->isAlive()) {
                if(ninja->distance(target) < 1) {
                    ninja->slash(target);
                }
                else {
                    ninja->move(target);
                }
            }
        }
    }

    int Team::stillAlive(){
        int counter = 0;
        for(size_t i = 0; i < members.size(); i++){
            if(members.at(i)->isAlive()) {
                counter++;
            }
        }
        return counter;
    }

    void Team::print(){

    }

    Character Team::getLeader() {
        return this->leader;
    }

    void Team::chooseLeader() {
        double distance = std::numeric_limits<double>::max();
        size_t index = (size_t)-1;
        
        for(size_t i = 0; i < members.size(); i++) {
            Character* optionalLeader = members.at(i);
            if (optionalLeader->isAlive() && optionalLeader != this->leader && optionalLeader->distance(this->leader) < distance) {
               distance = optionalLeader->distance(this->leader);
               index = i;
            }
        }
        
        if (index != -1) {
            this->leader = members.at(index);
        }
    }

    Character* Team::getTarget(Team* enemy) {
        double distance = std::numeric_limits<double>::max();
        size_t index = (size_t)-1;
        
        for(size_t i = 0; i < enemy->members.size(); i++) {
            Character* optionalTarget = enemy->members.at(i);
            
            if (optionalTarget->isAlive() && optionalTarget != this->leader && optionalTarget->distance(this->leader) < distance) {
               distance = optionalTarget->distance(this->leader);
               index = i;
            }
        }
        
        return (index != -1) ? enemy->members.at(index) : nullptr;
    }
}
