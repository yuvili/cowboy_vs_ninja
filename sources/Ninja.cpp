#include "Ninja.hpp"

// Constructors
Ninja::Ninja(){
    Character();
    _speed = 0;
}

Ninja::Ninja(const string& name, Point& possition){
    Character(name, possition);
    _speed = 0;
}

Ninja::Ninja(const string& name, Point& possition, int hits, int speed){
    Character(name, possition);
    hit_points = hits;
    _speed = speed;
}

Ninja::Ninja(const Ninja& character){}
Ninja::Ninja(Character* character){}
Ninja* Ninja::operator->() {return this;}

template <typename T>
void Ninja::move(T){

}
template <typename T>
void Ninja::slash(T){
    if(isAlive() && _possition.distance(T._possition) < 1){
        T.hit(13);
    }
}