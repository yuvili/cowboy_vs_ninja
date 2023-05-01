#include "doctest.h"
#include <stdexcept>
#include "sources/Team.hpp"
#include <iostream>
#include <typeinfo>
#include <sstream>
using namespace ariel;
using namespace std;

TEST_CASE("Point object initialization & Getters return expected values") {
    Point p(1, 2);

    SUBCASE("Check that the type of X and Y are double"){
        CHECK(typeid(p.getX()).name() == typeid(double).name());
        CHECK(typeid(p.getY()).name() == typeid(double).name());
    }

    SUBCASE("Check that the double constractor's fields are like expected"){
        CHECK(((p.getX() == 1) && (p.getY() == 2)));
    }
    
    SUBCASE("Check Point getters"){
        Point p2(3.14, 2.71);

        CHECK(p2.getX() == doctest::Approx(3.14));
        CHECK(p2.getY() == doctest::Approx(2.71));
    }

    SUBCASE("Check Point default constructor"){
        Point p3;
        CHECK(p3.getX() == doctest::Approx(0.0));
        CHECK(p3.getY() == doctest::Approx(0.0));
    }
}

TEST_CASE("Point moveTowards calculation") {
    Point p1(0.0, 0.0);
    Point p2(3.0, 4.0);
    Point target(5.0, 5.0);

    SUBCASE("Move towards target point") {
        Point& movedPoint = p1.moveTowards(p2, target, 2.0);
        CHECK(movedPoint.getX() == doctest::Approx(1.0));
        CHECK(movedPoint.getY() == doctest::Approx(1.0));
    }

    SUBCASE("Move towards target point when already at or beyond the target") {
        Point& movedPoint = p2.moveTowards(p1, target, 2.0);
        CHECK(movedPoint.getX() == doctest::Approx(3.0));
        CHECK(movedPoint.getY() == doctest::Approx(4.0));
    }
}

TEST_CASE("Point distance calculation") {
    Point p1(0.0, 0.0);
    Point p2(3.0, 4.0);

    SUBCASE("Distance between two points"){
        double distance = p1.distance(p2);
        CHECK(distance == doctest::Approx(5.0));
        CHECK(distance == p2.distance(p1));
    }

    SUBCASE("Distance to itself"){
        double distance = p1.distance(p1);
        CHECK(distance == doctest::Approx(0.0));
    }
}

TEST_CASE("Cowboy initialization") {
    Point p(3.14, 2.71);
    Cowboy cowboy("Hermione", p);
   
    CHECK(cowboy.isAlive() == true);
    CHECK(cowboy.getHitPoints() == 110);
    CHECK(cowboy.getName() == "Hermione");
    CHECK(cowboy.distance(&cowboy) == doctest::Approx(0.0));
    CHECK(cowboy.getLocation().getX() == doctest::Approx(3.14));
    CHECK(cowboy.getLocation().getY() == doctest::Approx(2.71));

    SUBCASE("Empty name") {
        Cowboy cowboyNone("", p);
        CHECK(cowboyNone.getName() == "");
    }  

    SUBCASE("Full name") {
        Cowboy cowboy2("Hermione Granger", p);
        CHECK(cowboy2.getName() == "Hermione Granger");
    } 

    SUBCASE("Check Cowboy default constructor") {
        Cowboy cowboy2;
        CHECK(cowboy2.getName() == "");
    }  
}

TEST_CASE("Cowboy isAlive") {
    Point p(0.0, 0.0);
    Cowboy cowboy("Minerva", p);

    SUBCASE("Alive cowboy") {
        cowboy.hit(20);
        CHECK(cowboy.isAlive() == true);
        CHECK(cowboy.getHitPoints() == 90);
    }

    SUBCASE("Dead cowboy") {
        cowboy.hit(100);
        CHECK(cowboy.isAlive() == false);
    }
}

TEST_CASE("Cowboy distance calculation") {
    Point p1(0.0, 0.0);
    Point p2(3.0, 4.0);
    Cowboy cowboy("Dumbledore", p1);
    Cowboy cowboy2("Snape", p2);

    double distance = cowboy.distance(&cowboy2);
    CHECK(distance == doctest::Approx(5.0));
}

TEST_CASE("Cowboy hit points") {
    Point p(0.0, 0.0);
    Cowboy cowboy("Ron", p);

    SUBCASE("Hit with damage") {
        cowboy.hit(20);
        CHECK(cowboy.getHitPoints() == 90);
    }

    SUBCASE("Hit with negative damage") {
        cowboy.hit(-10);
        CHECK(cowboy.getHitPoints() == 100);
    }

    SUBCASE("Negative hit points") {
        Cowboy cowboy("Neville", p);
        cowboy.hit(120);
        CHECK(cowboy.isAlive() == false);
        CHECK(cowboy.getHitPoints() == 0);
    }
}

TEST_CASE("Cowboy shoot") {
    Point p1(0.0, 0.0);
    Point p2(3.0, 4.0);
    Cowboy cowboy1("Bellatrix", p1);
    Cowboy cowboy2("Sirius", p2);

    SUBCASE("Shoot enemy with bullets left") {
        cowboy1.shoot(cowboy2);
        CHECK(cowboy2.getHitPoints() == 100);
        CHECK(cowboy1.hasBullets() == true);
    }

    SUBCASE("Shoot enemy with no bullets left") {
        cowboy1.shoot(cowboy2);
        cowboy1.shoot(cowboy2);
        cowboy1.shoot(cowboy2);
        cowboy1.shoot(cowboy2);
        cowboy1.shoot(cowboy2);
        CHECK(cowboy2.getHitPoints() == 50);
        cowboy1.shoot(cowboy2);
        CHECK(cowboy2.getHitPoints() == 50); // No damage as no bullets left
        CHECK(cowboy1.hasBullets() == false);
    }

     SUBCASE("Shoot self") {
        cowboy1.shoot(cowboy1);
        CHECK(cowboy1.getHitPoints() == 100); // No damage as shooting self
    }

    SUBCASE("Shoot null enemy") {
        Cowboy* enemy = nullptr;
        cowboy1.shoot(enemy);
        CHECK(cowboy1.getHitPoints() == 100); // No damage as shooting null enemy
    }
}

TEST_CASE("Cowboy reload") {
    Point p(0.0, 0.0);
    Cowboy cowboy("Harry", p);

    cowboy.reload();
    CHECK(cowboy.hasBullets() == true);
}

TEST_CASE("Team initialization") {
    Cowboy cowboy1("Harry", Point(1.0, 1.0));
    Cowboy cowboy2("Ron", Point(2.125, 2.5));
    Cowboy cowboy3("Neville", Point(1.0, 1.3));
    Cowboy cowboy4("Lavender", Point(2.25, 2.0));
    Cowboy cowboy5("Fred", Point(8.2, 9.1));
    YountNinja ninja1("Hermione", Point(1.22, 3.0));
    TrainedNinja ninja2("Luna", Point(1.5, 0.25));
    YountNinja ninja3("Ginny", Point(4.25, 9.1));
    TrainedNinja ninja4("Seamus", Point(3.0, 3.0));

    Team team1(&cowboy1);
    CHECK(team1.stillAlive() == 1);
    SUBCASE("Create team") {
        CHECK_NOTHROW(team1.add(&cowboy2));
        CHECK_NOTHROW(team1.add(&ninja1));
        CHECK_NOTHROW(team1.add(&ninja2));
        CHECK_NOTHROW(team1.add(&cowboy3));
        CHECK_NOTHROW(team1.add(&cowboy4));
        CHECK_NOTHROW(team1.add(&ninja3));
        CHECK_NOTHROW(team1.add(new OldNinja("Sirius", Point(7.05, 3.5))));
        CHECK_NOTHROW(team1.add(&cowboy5));
        CHECK_NOTHROW(team1.add(new Cowboy("George", Point(0.0, 2.125))));

        CHECK(team1.stillAlive() == 10);
    }
    
    SUBCASE("Adding too many characters"){
        CHECK_THROWS_AS(team1.add(&ninja4), std::runtime_error);
    }

    SUBCASE("Get Leader"){
        CHECK_EQ(team1.getLeader().getName(), "Harry");
    }
}

TEST_CASE("Team attack") {
    // Creat team1
    Cowboy cowboy1("Harry", Point(1.0, 1.0));
    Cowboy cowboy2("Ron", Point(1.25, 3.0));
    TrainedNinja ninja1("Hermione", Point(1.25, 3.0));
    YountNinja ninja2("Ginny", Point(4.25, 9.1));
    OldNinja ninja3("Neville", Point(7.05, 3.5));

    Team team1(&cowboy1);
    team1.add(&cowboy2);
    team1.add(&ninja1);
    team1.add(&ninja2);
    team1.add(&ninja3);

    // Create team 2
    Cowboy cowboy12("Draco", Point(1.5, 7.0));
    Cowboy cowboy22("Snape", Point(1.5, 1.125));
    OldNinja ninja12("Bellatrix", Point(1.5, 1.125));
    YountNinja ninja22("Lucius", Point(1.5, 0.75));

    Team team2(&cowboy12);
    team2.add(&cowboy22);
    team2.add(&ninja12);
    team2.add(&ninja22);

    SUBCASE("Attacking with living members") {
        // Attack team2 with team1
        team1.attack(&team2);

        // Check if expected number of team members are alive after the attack
        CHECK(team1.stillAlive() == 5);
        CHECK(team2.stillAlive() == 4);

        CHECK(ninja22.getHitPoints() == 90); // ninja22 is the closest alive player to team1 leader 

        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);

        CHECK(team1.stillAlive() == 5);
        CHECK(team2.stillAlive() == 3);

        // ninja22 is the closest alive player to team1 leader 
        CHECK(ninja22.getHitPoints() == 0);
        CHECK_FALSE(ninja22.isAlive()); 

        team1.attack(&team2);
        CHECK(cowboy22.getHitPoints() == 100); // cowboy32 is the closest alive player to team1 leader 
    }

    SUBCASE("Attacking the team leader") {
    
    }

}