#include "Ninja.hpp"

// Constructors
// Ninja::Ninja() : Character(), _speed(0) {}

// Ninja::Ninja(string name, Point possition) : Character(name, possition, 0) , _speed(0) {}

Ninja::Ninja(const string& name, Point& possition, int hits, int speed) : Character(name, possition, hits), _speed(speed) {}

// Ninja::Ninja(Ninja& ninja) : Ninja(ninja._name, ninja._possition, ninja.hit_points, ninja._speed) {}

// Ninja::Ninja(Ninja&& other) noexcept{
//     this->_name = other._name;
//     this->_possition = other._possition;
//     this->hit_points = other.hit_points;
//     this->inTeam = other.inTeam;
//     this->_speed = other._speed;
// }

// Ninja* Ninja::operator->() {return this;}

// Ninja& Ninja::operator=(const Ninja& other) {
//     this->_name = other._name;
//     this->_possition = other._possition;
//     this->hit_points = other.hit_points;
//     this->inTeam = other.inTeam;
//     this->_speed = other._speed;
//     return *this;
// }

// Ninja& Ninja::operator=(Ninja&& other) noexcept{
//     this->_name = other._name;
//     this->_possition = other._possition;
//     this->hit_points = other.hit_points;
//     this->inTeam = other.inTeam;
//     this->_speed = other._speed;
//     return *this;
// }

// YountNinja::YountNinja() : Ninja() {
//     hit_points = 100;
//     _speed = 14;
// }

YountNinja::YountNinja(const string& name, Point possition) : Ninja(name, possition, 100, 14) {}

// TrainedNinja::TrainedNinja() : Ninja() {
//     hit_points = 120;
//     _speed = 12;
// }
TrainedNinja::TrainedNinja(const string& name, Point possition) : Ninja(name, possition, 120, 12) {}

// OldNinja::OldNinja() : Ninja() {
//     hit_points = 150;
//     _speed = 8;
// }
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
    return "(N) (Name: " + _name + "), Position: " + getLocation().print();
}