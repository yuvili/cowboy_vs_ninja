#ifndef NINJA_HPP
#define NINJA_HPP
#include <string>
#include "Character.hpp"
using namespace std;

class Ninja : public Character {
    protected:
        int _speed;

    public:
        // Constructors
        Ninja();
        Ninja(const string&, Point&);
        Ninja(const string&, Point&, int, int);
        Ninja(const Ninja& character);
        Ninja(Character* character);
        Ninja* operator->();

        // Functions
        template <typename T>
        void move(T);
        template <typename T>
        void slash(T);
};
#endif