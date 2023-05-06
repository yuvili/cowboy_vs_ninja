#include "Ninja.hpp"

// Constructors
Ninja::Ninja() : Character() {
    _speed = 0;
}

Ninja::Ninja(string name, Point possition) : Character(name, possition, 0) {
    _speed = 0;
}

Ninja::Ninja(const string& name, Point& possition, int hits, int speed) : Character(name, possition, hits) {
    _speed = speed;
}

Ninja::Ninja(const Ninja& character){}
Ninja::Ninja(Character* character){}
Ninja* Ninja::operator->() {return this;}

void Ninja::move(Character *enemy){
    _possition = getLocation().moveTowards(_possition, enemy->_possition, _speed);
}

void Ninja::slash(Character *enemy){
    if(isAlive() && _possition.distance(enemy->_possition) < 1 && enemy != nullptr && this != enemy){
        enemy->hit(13);
    }
}

string Ninja::print() {
    return "(N) " + this->Character::print();
}