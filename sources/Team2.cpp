#include "Team2.hpp"

void Team2::attack(Team* enemy){
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
            else {
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
}