#ifndef TRAINEDNINJA_HPP
#define TRAINEDNINJA_HPP
#include <string>
#include "Ninja.hpp"
#include "Character.hpp"
using namespace std;

class TrainedNinja : public Ninja {
    public:
        TrainedNinja() : Ninja() {
            hit_points = 120;
            _speed = 12;
        }
        TrainedNinja(const string& name, Point possition) : Ninja(name, possition) {
            hit_points = 120;
            _speed = 12;
        }
        TrainedNinja(const TrainedNinja& character){}
        TrainedNinja(Character* character){}
};
#endif