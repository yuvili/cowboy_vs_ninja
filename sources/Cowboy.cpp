#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include "Cowboy.hpp"

// Constructor
Cowboy::Cowboy(string name, Point possition) : Character(name, possition, 110) {
    bullets_count = 6;
}

// Functions
void Cowboy::shoot(Character *enemy){
    if(enemy == this) {
        throw std::runtime_error("Can't shoot self.");
    }
    
    if(!enemy->isAlive()) {
        throw std::runtime_error("Enemy is already dead.");
    }

    if(!isAlive()) {
        throw std::runtime_error("Dead cowboy can't shoot");
    }

    if(isAlive() && hasBullets() && enemy != nullptr && this != enemy){
        enemy->hit(10);
        bullets_count -= 1;
    }
}

bool Cowboy::hasBullets(){
    return bullets_count > 0;
}

void Cowboy::reload(){
    if(!isAlive()) {
        throw std::runtime_error("Can't reload to dead cowboy.");
    }
    bullets_count += 6;
}

string Cowboy::print() {
    if(isAlive()){
        return "(C) Name: " + _name + ", Position: " + _possition.print() + ", Hit Points: " + to_string(hit_points);
    }
    return "(C) Name: (" + _name + "), Position: " + _possition.print();
}