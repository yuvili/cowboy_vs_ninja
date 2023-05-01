#ifndef OLDNINJA_HPP
#define OLDNINJA_HPP
#include <string>
#include "Character.hpp"
#include "Ninja.hpp"
using namespace std;

class OldNinja : public Ninja {
    public:
        OldNinja(){}
        OldNinja(const string&, Point){}
        OldNinja(const OldNinja& character){}
        OldNinja(Character* character){}
};
#endif