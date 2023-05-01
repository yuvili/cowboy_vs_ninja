#ifndef COWBOY_HPP
#define COWBOY_HPP
#include <string>
#include "Character.hpp"
using namespace std;

class Cowboy : public Character {
    private:
        // Variables
        int boolets_count;

    public:
        // Constructors
        Cowboy(const string&, Point&){}
        Cowboy(const Cowboy& character){}
        Cowboy(Character* character){}
        Cowboy* operator->() {return this;}

        // Functions
        template <typename T>
        void shoot(T);
        bool hasboolets();
        void reload();
};
#endif
