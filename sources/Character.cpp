#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "Character.hpp"

// Constructors
Character::Character() : _name(""), _possition(Point()), hit_points(0), inTeam(false) {}

Character::Character(string name, Point possition, int hit_points){
    this->_name = name;
    this->_possition = possition;
    this->hit_points = hit_points;
    this->inTeam = false;
}
Character::Character(const Character& other) : Character(other._name, other._possition, other.hit_points) {}

Character::Character(Character* other) : Character(other->_name, other->_possition, other->hit_points){}

Character::Character(Character&& other) noexcept{}

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

Point Character::getLocation(){
    return _possition;
}

string Character::print(){
    if(isAlive()){
        return  _name + " " + to_string(hit_points) + " ";
    }
    return  _name + " ";
}

int Character::getHitPoints(){
    return hit_points;
}

void Character::setInTeam(bool newSet) {
    this->inTeam = newSet;
}