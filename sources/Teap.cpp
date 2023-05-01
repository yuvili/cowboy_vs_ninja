#include <string>
#include <stdexcept>
using namespace std;

#include "Team.hpp"

namespace ariel {
    void Team::add(Character* member){
        if(members.size() > 10){
            throw std::runtime_error("Max characters in team excided.");
        }
        

    }
    void Team::attack(Team*){

    }
    int Team::stillAlive(){

    }
    void Team::Print(){

    }
}
