#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include "Cowboy.hpp"

// Constructors
Cowboy::Cowboy() : Character() {
    hit_points = 110;
    bullets_count = 6;
}

Cowboy::Cowboy(string name, Point possition) : Character(name, possition, 110) {
    bullets_count = 6;
}

Cowboy::Cowboy(Cowboy* character) : Cowboy(character->getName(), character->getLocation()){}

Cowboy* Cowboy::operator->() {return this;}

// Functions
void Cowboy::shoot(Character *enemy){
    if(isAlive() && hasBullets() && enemy != nullptr && this != enemy){
        enemy->hit(10);
        bullets_count -= 1;
    }
}

bool Cowboy::hasBullets(){
    return bullets_count > 0;
}

void Cowboy::reload(){
    bullets_count += 6;
}

string Cowboy::print() {
    return "(C) " + this->Character::print();
}