#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <string>
#include "Point.hpp"
using namespace std;

class Character{
    public:
        // Constructors
        Character();
        Character(const string&, Point&); // check overflow of double? when reciev float??
        ~Character(); // Destructor
        Character(const Character& other){}
        Character(Character* other){}
        Character(Character&& other) noexcept; // Move constructor

        // Variables
        Point possition;
        int hit_points;;
        string name;

        // Functions
        bool isAlive();
        double distance(Character*);
        void hit(int damage);
        string getName();
        Point getLocation();
        string Print();
};
#endif