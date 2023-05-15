#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <iostream>
#include <string>
#include "Point.hpp"
using namespace std;

class Character{
    public:
        // Constructors
        Character();
        Character(string, Point, int);
        virtual ~Character(); // Destructor
        Character(const Character& other);
        Character(Character* other);
        Character(Character&& other) noexcept; // Move constructor

        Character& operator=(const Character&);
        Character& operator=(Character&&) noexcept;

        // Variables
        Point _possition;
        int hit_points;
        string _name;
        bool inTeam;

        // Functions
        virtual bool isAlive(); 
        virtual double distance(Character*);
        virtual void hit(int damage); 
        virtual string print() = 0;
        
        // Getters & Setters
        string getName();
        Point& getLocation();
        int getHitPoints();
        bool getInTeam();
        void setInTeam(bool);
};
#endif