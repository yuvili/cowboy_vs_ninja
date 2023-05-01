#ifndef TRAINEDNINJA_HPP
#define TRAINEDNINJA_HPP
#include <string>
#include "Ninja.hpp"
#include "Character.hpp"
using namespace std;

class TrainedNinja : public Ninja {
    public:
        TrainedNinja(){}
        TrainedNinja(const string&, Point){}
        TrainedNinja(const TrainedNinja& character){}
        TrainedNinja(Character* character){}
};
#endif