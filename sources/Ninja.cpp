#include "Ninja.hpp"

// Constructors
Ninja::Ninja(const string& name, Point& possition, int hits, int speed) : Character(name, possition, hits), _speed(speed) {}

YoungNinja::YoungNinja(const string& name, Point possition) : Ninja(name, possition, 100, 14) {}

TrainedNinja::TrainedNinja(const string& name, Point possition) : Ninja(name, possition, 120, 12) {}

OldNinja::OldNinja(const string& name, Point possition) : Ninja(name, possition, 150, 8) {}

void Ninja::move(Character *enemy){
    _possition = getLocation().moveTowards(_possition, enemy->getLocation(), _speed);
}

void Ninja::slash(Character *enemy){
    if(enemy == this) {
        throw std::runtime_error("Can't slash self.");
    }

    if(!enemy->isAlive()) {
        throw std::runtime_error("Enemy is already dead.");
    }

    if(!isAlive()) {
        throw std::runtime_error("Dead ninja can't slash");
    }

    if(isAlive() && _possition.distance(enemy->getLocation()) < 1 && enemy != nullptr && this != enemy){
        enemy->hit(13);
    }
}

string Ninja::print() {
     if(isAlive()){
        return "(N) Name: " + _name + ", Position: " + getLocation().print() + ", Hit Points: " + to_string(hit_points);
    }
    return "(N) Name: (" + _name + "), Position: " + getLocation().print();
}