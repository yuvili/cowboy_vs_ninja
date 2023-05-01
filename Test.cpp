#include "doctest.h"
#include <stdexcept>
#include "sources/Team.hpp"
#include <iostream>
#include <typeinfo>
#include <sstream>
using namespace ariel;
using namespace std;

TEST_CASE("Fraction object initialization & Getters return expected values") {
    Point p(1, 2);

    // Check that the type of X and Y are double
    CHECK(typeid(p.getX()).name() == typeid(double).name());
    CHECK(typeid(p.getY()).name() == typeid(double).name());

    // Check that the int constractor's fields are like expected. Also checks the getters
    CHECK(((p.getX() == 1) && (p.getY() == 2)));
}