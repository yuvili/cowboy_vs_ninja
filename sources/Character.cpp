#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "Character.hpp"

// Constructors
//Character::Character() : _name(""), _possition(Point()), hit_points(0), inTeam(false) {}

Character::Character(string name, Point possition, int hit_points) : _name(name), _possition(possition), hit_points(hit_points), inTeam(false) {}

Character::~Character() {}

// Character::Character(const Character& other) : Character(other._name, other._possition, other.hit_points) {}

// Character::Character(Character* other) : Character(other->_name, other->_possition, other->hit_points){}

// Character::Character(Character&& other) noexcept : _name(other._name), _possition(other._possition), hit_points(other.hit_points), inTeam(other.inTeam){}

// Character& Character::operator=(const Character& other){
//     this->_name = other._name;
//     this->_possition = other._possition;
//     this->hit_points = other.hit_points;
//     this->inTeam = other.inTeam;
//     return *this;
// }

// Character& Character::operator=(Character&& other) noexcept{
//     this->_name = other._name;
//     this->_possition = other._possition;
//     this->hit_points = other.hit_points;
//     this->inTeam = other.inTeam;
//     return *this;
// }

// Functions
bool Character::isAlive(){
    return this->hit_points > 0;
}

double Character::distance(Character* other){
    return _possition.distance(other->_possition);
}

void Character::hit(int damage){
    this->hit_points -= damage;
}

string Character::getName(){
    return this->_name;
}

Point& Character::getLocation(){
    return _possition;
}

int Character::getHitPoints(){
    return hit_points;
}

bool Character::getInTeam() {
    return inTeam;
}

void Character::setInTeam(bool newSet) {
    this->inTeam = newSet;
}