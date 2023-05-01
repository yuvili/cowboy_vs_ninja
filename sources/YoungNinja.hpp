#ifndef YOUNGNINJA_HPP
#define YOUNGNINJA_HPP
#include <string>
#include "Character.hpp"
#include "Ninja.hpp"
using namespace std;

class YountNinja : public Ninja {
    public:
        YountNinja(){
            Ninja();
            hit_points = 100;
            _speed = 14;
        }
        YountNinja(const string& name, Point possition){
            Ninja(name, possition);
            hit_points = 100;
            _speed = 14;
        }
        YountNinja(const YountNinja& character){}
        YountNinja(Character* character){}
};
#endif