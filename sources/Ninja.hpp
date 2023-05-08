#ifndef NINJA_HPP
#define NINJA_HPP
#include <string>
#include "Character.hpp"
using namespace std;


class Ninja : public Character {
    public:
        // Constructors
        // Ninja();
        // Ninja(string, Point);
        Ninja(const string&, Point&, int, int);
        // Ninja(Ninja& character);
        // Ninja(Ninja&& character) noexcept;
        // Ninja* operator->();
        // Ninja& operator=(const Ninja&);
        // Ninja& operator=(Ninja&&) noexcept;

        // Functions
        virtual void move(Character *enemy);
        virtual void slash(Character *enemy);
        string print();

        int _speed;
};

class YountNinja : public Ninja {
    public:
        // YountNinja();
        YountNinja(const string& name, Point possition);
};

class TrainedNinja : public Ninja {
    public:
        //TrainedNinja();
        TrainedNinja(const string& name, Point possition);
};

class OldNinja : public Ninja {
    public:
        //OldNinja();
        OldNinja(const string& name, Point possition);
};
#endif