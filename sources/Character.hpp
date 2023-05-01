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
        Point _possition;
        int hit_points;
        string _name;

        // Functions
        bool isAlive(); // Returns true if hit_points > 0
        double distance(Character*);
        void hit(int damage); // Subtracts the damge value from hit_points
        string getName();
        Point getLocation();
        string Print();
        int getHitPoints();
};
#endif