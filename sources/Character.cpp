#include "Character.hpp"
// Constructors
Character::Character() : _name(""), _possition(Point()), hit_points(0) {}

Character::Character(const string& name, Point& possition) : _name(name), _possition(possition), hit_points(0) {}

Character::~Character(){}
// Character::Character(const Character& other){
    
// }
Character::Character(Character&& other){}

// Functions
bool Character::isAlive(){
    return hit_points > 0;
}
double Character::distance(Character* other){
    return _possition.distance(other->_possition);

}
void Character::hit(int damage){
    hit_points -= damage;
}

string Character::getName(){
    return _name;
}
Point Character::getLocation(){
    return _possition;
}

string Character::Print(){
    if(isAlive()){
        return  _name + " " + to_string(hit_points) + " ";
    }
    return  _name + " ";
}