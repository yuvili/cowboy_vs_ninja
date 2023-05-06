#ifndef OLDNINJA_HPP
#define OLDNINJA_HPP
#include <string>
#include "Character.hpp"
#include "Ninja.hpp"
using namespace std;

class OldNinja : public Ninja {
    public:
        OldNinja() : Ninja(){
            hit_points = 150;
            _speed = 8;
        }
        OldNinja(const string& name, Point possition) : Ninja(name, possition) {
            hit_points = 150;
            _speed = 8;
        }
        OldNinja(const OldNinja& character){}
        OldNinja(Character* character){}
};
#endif