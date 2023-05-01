#include "Cowboy.hpp"

// Constructors
Cowboy::Cowboy(){
    Character();
    hit_points = 110;
    bullets_count = 6;
}
Cowboy::Cowboy(const string& name, Point possition){
    Character(name, possition);
    hit_points = 110;
    bullets_count = 6;
}
Cowboy::Cowboy(const Cowboy& cowboy){
    Character(cowboy);
    bullets_count = cowboy.bullets_count;
}
Cowboy::Cowboy(Character* character){}
Cowboy* Cowboy::operator->() {return this;}

// Functions
template <typename T>
void Cowboy::shoot(T){
    if(isAlive() && hasBullets()){
        T.hit(10);
        bullets_count -= 1;
    }

}
bool Cowboy::hasBullets(){
    return bullets_count > 0;
}

void Cowboy::reload(){
    bullets_count += 6;
}