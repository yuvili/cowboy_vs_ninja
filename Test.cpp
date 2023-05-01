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