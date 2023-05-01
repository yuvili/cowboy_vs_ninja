#ifndef YOUNGNINJA_HPP
#define YOUNGNINJA_HPP
#include <string>
#include "Character.hpp"
#include "Ninja.hpp"
using namespace std;

class YountNinja : public Ninja {
    public:
        YountNinja(){}
        YountNinja(const string&, Point){}
        YountNinja(const YountNinja& character){}
        YountNinja(Character* character){}
};
#endif