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

    // Check that the type of X and Y are double
    CHECK(typeid(p.getX()).name() == typeid(double).name());
    CHECK(typeid(p.getY()).name() == typeid(double).name());

    // Check that the double constractor's fields are like expected. Also checks the getters
    CHECK(((p.getX() == 1) && (p.getY() == 2)));
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