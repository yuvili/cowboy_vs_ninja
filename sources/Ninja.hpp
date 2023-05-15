#ifndef NINJA_HPP
#define NINJA_HPP
#include <string>
#include "Character.hpp"
using namespace std;


class Ninja : public Character {
    public:
        // Constructor
        Ninja(const string&, Point&, int, int);

        // Functions
        virtual void move(Character *enemy);
        virtual void slash(Character *enemy);
        string print() override;

        int _speed;
};

class YoungNinja : public Ninja {
    public:
        YoungNinja(const string& name, Point possition);
};

class TrainedNinja : public Ninja {
    public:
        TrainedNinja(const string& name, Point possition);
};

class OldNinja : public Ninja {
    public:
        OldNinja(const string& name, Point possition);
};
#endif