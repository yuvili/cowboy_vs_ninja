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

    SUBCASE("Check print") {
        Point p2(3.14, 2.71);
        CHECK(p2.print() == "(3.140000,2.710000)");
    } 
}

TEST_CASE("Point moveTowards calculation") {
    Point p1(5.0, 0.0);
    Point p2(3.0, 4.0);
    Point target(5.0, 4.0);

    SUBCASE("Move towards target point") {
        Point movedPoint = p1.moveTowards(p1, target, 2.0);
        CHECK(movedPoint.getX() == doctest::Approx(5.0));
        CHECK(movedPoint.getY() == doctest::Approx(2.0));
    }

    SUBCASE("Move towards target point when already at or beyond the target") {
        Point movedPoint = p2.moveTowards(p2, target, 2.0);
        CHECK(movedPoint.getX() == doctest::Approx(5.0));
        CHECK(movedPoint.getY() == doctest::Approx(4.0));
    }

    SUBCASE("Move negative distance throws error") {
        CHECK_THROWS(p2.moveTowards(p2, target, -2.0));
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
    Cowboy *cowboy = new Cowboy("Hermione", p);
   
    CHECK(cowboy->isAlive() == true);
    CHECK(cowboy->getHitPoints() == 110);
    CHECK(cowboy->getName() == "Hermione");
    CHECK(cowboy->distance(cowboy) == doctest::Approx(0.0));
    CHECK(cowboy->getLocation().getX() == doctest::Approx(3.14));
    CHECK(cowboy->getLocation().getY() == doctest::Approx(2.71));

    SUBCASE("Empty name") {
        Cowboy *cowboyNone = new Cowboy("", p);
        CHECK(cowboyNone->getName() == "");
    }  

    SUBCASE("Full name") {
        Cowboy *cowboy2 = new Cowboy("Hermione Granger", p);
        CHECK(cowboy2->getName() == "Hermione Granger");
    }

    SUBCASE("Check print") {
        Cowboy *cowboy2 = new Cowboy("Hermione Granger", p);
        CHECK(cowboy2->print() == "(C) Name: Hermione Granger, Position: (3.140000,2.710000), Hit Points: 110");
    } 
}

TEST_CASE("Cowboy isAlive") {
    Point p(0.0, 0.0);
    Cowboy *cowboy = new Cowboy("Minerva", p);

    SUBCASE("Alive cowboy") {
        cowboy->hit(20);
        CHECK(cowboy->isAlive() == true);
        CHECK(cowboy->getHitPoints() == 90);
    }

    SUBCASE("Dead cowboy") {
        cowboy->hit(110);
        CHECK(cowboy->getHitPoints() == 0);
        CHECK_FALSE(cowboy->isAlive());
    }
}

TEST_CASE("Cowboy distance calculation") {
    Point p1(0.0, 0.0);
    Point p2(3.0, 4.0);
    Cowboy *cowboy = new Cowboy("Dumbledore", p1);
    Cowboy *cowboy2 = new Cowboy("Snape", p2);

    double distance = cowboy->distance(cowboy2);
    CHECK(distance == doctest::Approx(5.0));
}

TEST_CASE("Cowboy hit points") {
    Point p(0.0, 0.0);
    Cowboy *cowboy = new Cowboy("Ron", p);

    SUBCASE("Hit with damage") {
        cowboy->hit(20);
        CHECK(cowboy->getHitPoints() == 90);
    }

    SUBCASE("Hit with negative damage") {
        cowboy->hit(-10);
        CHECK(cowboy->getHitPoints() == 120);
    }

    SUBCASE("Negative hit points") {
        cowboy->hit(120);
        CHECK(cowboy->isAlive() == false);
        CHECK(cowboy->getHitPoints() == -10);
    }

    SUBCASE("Print after hit and death") {
        cowboy->hit(90);
        CHECK(cowboy->print() == "(C) Name: Ron, Position: (0.000000,0.000000), Hit Points: 20");
        
        cowboy->hit(20);
        CHECK(cowboy->print() == "(C) Name: (Ron), Position: (0.000000,0.000000)");
    }
}

TEST_CASE("Cowboy shoot") {
    Point p1(0.0, 0.0);
    Point p2(3.0, 4.0);
    Cowboy *cowboy1 = new Cowboy("Bellatrix", p1);
    Cowboy *cowboy2 = new Cowboy("Sirius", p2);

    SUBCASE("Shoot enemy with bullets left") {
        cowboy1->shoot(cowboy2);
        CHECK(cowboy2->getHitPoints() == 100);
        CHECK(cowboy1->hasBullets() == true);
    }

    SUBCASE("Shoot enemy with no bullets left") {
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        CHECK(cowboy2->getHitPoints() == 50);
        cowboy1->shoot(cowboy2);
        CHECK(cowboy2->getHitPoints() == 50); // No damage as no bullets left
        CHECK(cowboy1->hasBullets() == false);
    }

     SUBCASE("Shoot self") {
        CHECK_THROWS(cowboy1->shoot(cowboy1));
    }

    SUBCASE("Cowboy shoots when dead or when enemy is dead") {
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        cowboy1->reload();
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        CHECK_FALSE(cowboy2->isAlive());
        CHECK_THROWS(cowboy1->shoot(cowboy2));
        CHECK_THROWS(cowboy2->shoot(cowboy1));
    }
}

TEST_CASE("Cowboy reload") {
    Point p(0.0, 0.0);
    Cowboy *cowboy1 = new Cowboy("Harry", p);
    Cowboy *cowboy2 = new Cowboy("Sirius", p);

    cowboy1->shoot(cowboy2);
    cowboy1->shoot(cowboy2);
    cowboy1->shoot(cowboy2);
    cowboy1->shoot(cowboy2);
    cowboy1->shoot(cowboy2);
    cowboy1->shoot(cowboy2);
    CHECK_FALSE(cowboy1->hasBullets());

    cowboy1->reload();
    CHECK(cowboy1->hasBullets());

    SUBCASE("Reload when cowboy is dead") {
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        cowboy1->shoot(cowboy2);
        CHECK_FALSE(cowboy2->isAlive());
        CHECK_THROWS(cowboy2->reload());
    }
}

TEST_CASE("Ninja initialization") {
    Point p(3.14, 2.71);
    
    YoungNinja *youngNinja = new YoungNinja("Hermione", p);
    CHECK(youngNinja->isAlive() == true);
    CHECK(youngNinja->getHitPoints() == 100);
    CHECK(youngNinja->getName() == "Hermione");
    CHECK(youngNinja->distance(youngNinja) == doctest::Approx(0.0));
    CHECK(youngNinja->getLocation().getX() == doctest::Approx(3.14));
    CHECK(youngNinja->getLocation().getY() == doctest::Approx(2.71));

    TrainedNinja *trainedNinja = new TrainedNinja("Snape", p);
    CHECK(trainedNinja->isAlive() == true);
    CHECK(trainedNinja->getHitPoints() == 120);
    CHECK(trainedNinja->getName() == "Snape");
    CHECK(trainedNinja->distance(trainedNinja) == doctest::Approx(0.0));
    CHECK(trainedNinja->getLocation().getX() == doctest::Approx(3.14));
    CHECK(trainedNinja->getLocation().getY() == doctest::Approx(2.71));

    OldNinja *oldNinja = new OldNinja("Dumbledore", p);
    CHECK(oldNinja->isAlive() == true);
    CHECK(oldNinja->getHitPoints() == 150);
    CHECK(oldNinja->getName() == "Dumbledore");
    CHECK(oldNinja->distance(oldNinja) == doctest::Approx(0.0));
    CHECK(oldNinja->getLocation().getX() == doctest::Approx(3.14));
    CHECK(oldNinja->getLocation().getY() == doctest::Approx(2.71));

    SUBCASE("Empty name") {
        YoungNinja *youngNinjaNone = new YoungNinja("", p);
        CHECK(youngNinjaNone->getName() == "");

        TrainedNinja *trainedNinjaNone = new TrainedNinja("", p);
        CHECK(trainedNinjaNone->getName() == "");

        OldNinja *oldNinjaNone = new OldNinja("", p);
        CHECK(oldNinjaNone->getName() == "");
    }  

    SUBCASE("Full name") {
        YoungNinja *youngNinja = new YoungNinja("Hermione Granger", p);
        CHECK(youngNinja->getName() == "Hermione Granger");
        
        TrainedNinja *trainedNinja = new TrainedNinja("Severus Snape", p);
        CHECK(trainedNinja->getName() == "Severus Snape");

        OldNinja *oldNinja = new OldNinja("Albus Dumbledore", p);
        CHECK(oldNinja->getName() == "Albus Dumbledore");
    }  

    SUBCASE("Check print") {
        CHECK(youngNinja->print() == "(N) Name: Hermione, Position: (3.140000,2.710000), Hit Points: 100");
        
        CHECK(trainedNinja->print() == "(N) Name: Snape, Position: (3.140000,2.710000), Hit Points: 120");

        CHECK(oldNinja->print() == "(N) Name: Dumbledore, Position: (3.140000,2.710000), Hit Points: 150");
    } 
}

TEST_CASE("Ninja isAlive") {
    Point p(1.0, 8.5);
    YoungNinja *youngNinja = new YoungNinja("Hermione", p);
    TrainedNinja *trainedNinja = new TrainedNinja("Snape", p);
    OldNinja *oldNinja = new OldNinja("Dumbledore", p);
   
    SUBCASE("Alive ninja") {
        youngNinja->hit(20);
        CHECK(youngNinja->isAlive() == true);
        CHECK(youngNinja->getHitPoints() == 80);

        trainedNinja->hit(20);
        CHECK(trainedNinja->isAlive() == true);
        CHECK(trainedNinja->getHitPoints() == 100);

        oldNinja->hit(20);
        CHECK(oldNinja->isAlive() == true);
        CHECK(oldNinja->getHitPoints() == 130);
    }

    SUBCASE("Dead ninja") {
        youngNinja->hit(100);
        CHECK_FALSE(youngNinja->isAlive());
        CHECK(youngNinja->getHitPoints() == 0);

        trainedNinja->hit(120);
        CHECK_FALSE(trainedNinja->isAlive());
        CHECK(trainedNinja->getHitPoints() == 0);

        oldNinja->hit(150);
        CHECK_FALSE(oldNinja->isAlive());
        CHECK(oldNinja->getHitPoints() == 0);
    }
}

TEST_CASE("Ninja hit points") {
    Point p(1.0, 8.5);
    YoungNinja *youngNinja = new YoungNinja("Hermione", p);
    TrainedNinja *trainedNinja = new TrainedNinja("Snape", p);
    OldNinja *oldNinja = new OldNinja("Dumbledore", p);

    SUBCASE("Hit with negative damage") {
        youngNinja->hit(-10);
        CHECK(youngNinja->getHitPoints() == 110);

        trainedNinja->hit(-10);
        CHECK(trainedNinja->getHitPoints() == 130);

        oldNinja->hit(-10);
        CHECK(oldNinja->getHitPoints() == 160);
    }

    SUBCASE("Negative hit points") {
        youngNinja->hit(110);
        CHECK(youngNinja->getHitPoints() == -10);
        CHECK_FALSE(youngNinja->isAlive());

        trainedNinja->hit(130);
        CHECK(trainedNinja->getHitPoints() == -10);
        CHECK_FALSE(trainedNinja->isAlive());

        oldNinja->hit(160);
        CHECK(oldNinja->getHitPoints() == -10);
        CHECK_FALSE(oldNinja->isAlive());
    }

    SUBCASE("Print after hit and death") {
        youngNinja->hit(90);
        CHECK(youngNinja->print() == "(N) Name: Hermione, Position: (1.000000,8.500000), Hit Points: 10");
        
        trainedNinja->hit(130);
        CHECK(trainedNinja->print() == "(N) Name: (Snape), Position: (1.000000,8.500000)");

        oldNinja->hit(50);
        CHECK(oldNinja->print() == "(N) Name: Dumbledore, Position: (1.000000,8.500000), Hit Points: 100");
    }
}

TEST_CASE("Ninja slash") {
    Point p1(0.0, 0.0);
    Point p2(0.25, 0.5);
    Point p3(3.0, 4.0);
    YoungNinja *youngNinja = new YoungNinja("Hermione", p1);
    TrainedNinja *trainedNinja = new TrainedNinja("Snape", p2);
    OldNinja *oldNinja = new OldNinja("Dumbledore", p3);

    SUBCASE("Slash when enemy is less then 1 meter away") {
        youngNinja->slash(trainedNinja);
        CHECK(trainedNinja->getHitPoints() == 107);

        trainedNinja->slash(youngNinja);
        CHECK(youngNinja->getHitPoints() == 87);
    }

    SUBCASE("Slash when enemy is more then 1 meter away") {
        youngNinja->slash(oldNinja);
        CHECK(oldNinja->getHitPoints() == 150);
    }

     SUBCASE("Slash self") {
        CHECK_THROWS(youngNinja->slash(youngNinja));
        CHECK_THROWS(trainedNinja->slash(trainedNinja));
        CHECK_THROWS(oldNinja->slash(oldNinja));
    }

    SUBCASE("Ninja slashes when dead or when enemy is dead") {
        trainedNinja->slash(youngNinja);
        trainedNinja->slash(youngNinja);
        trainedNinja->slash(youngNinja);
        trainedNinja->slash(youngNinja);
        trainedNinja->slash(youngNinja);
        trainedNinja->slash(youngNinja);
        trainedNinja->slash(youngNinja);
        trainedNinja->slash(youngNinja);
        CHECK_FALSE(youngNinja->isAlive());
        CHECK_THROWS(trainedNinja->slash(youngNinja));
        CHECK_THROWS(youngNinja->slash(trainedNinja));
    }
}

TEST_CASE("Team initialization") {
    Cowboy* cowboy1 = new Cowboy("Harry", Point(1.0, 1.0));
    Cowboy* cowboy2 = new Cowboy("Ron", Point(2.125, 2.5));
    Cowboy* cowboy3 = new Cowboy("Neville", Point(1.0, 1.3));
    Cowboy* cowboy4 = new Cowboy("Lavender", Point(2.25, 2.0));
    Cowboy* cowboy5 = new Cowboy("Fred", Point(8.2, 9.1));
    YoungNinja* ninja1 = new YoungNinja("Hermione", Point(1.22, 3.0));
    TrainedNinja* ninja2 = new TrainedNinja("Luna", Point(1.5, 0.25));
    YoungNinja* ninja3 = new YoungNinja("Ginny", Point(4.25, 9.1));
    TrainedNinja* ninja4 = new TrainedNinja("Seamus", Point(3.0, 3.0));

    Team team1(cowboy1);
    CHECK(team1.stillAlive() == 1);

    CHECK_NOTHROW(team1.add(cowboy2));
    CHECK_NOTHROW(team1.add(ninja1));
    CHECK_NOTHROW(team1.add(ninja2));
    CHECK_NOTHROW(team1.add(cowboy3));
    CHECK_NOTHROW(team1.add(cowboy4));
    CHECK_NOTHROW(team1.add(ninja3));
    CHECK_NOTHROW(team1.add(new OldNinja("Sirius", Point(7.05, 3.5))));
    CHECK_NOTHROW(team1.add(cowboy5));
    CHECK_NOTHROW(team1.add(new Cowboy("George", Point(0.0, 2.125))));

    CHECK(team1.stillAlive() == 10);

    SUBCASE("Check leader") {
        CHECK_EQ(team1.getLeader()->getName(), "Harry");
    }
    
    SUBCASE("Adding too many characters") {
        CHECK_THROWS(team1.add(ninja4));
    }

    SUBCASE("Adding member of another team"){
        TrainedNinja* ninja21 = new TrainedNinja("Seamus", Point(3.0, 3.0));
        Team team2(ninja21);
        CHECK_THROWS(team1.add(ninja21));
    }

    SUBCASE("Print team"){
        // Redirect cout to stringstream
        std::stringstream out;
        std::streambuf* cout_buf = std::cout.rdbuf();
        std::cout.rdbuf(out.rdbuf());

        team1.print();

        std::cout.rdbuf(cout_buf);

        std::string expected_out = "Team members:\n   (C) Name: Harry, Position: (1.000000,1.000000), Hit Points: 110\n   (C) Name: Ron, Position: (2.125000,2.500000), Hit Points: 110\n   (C) Name: Neville, Position: (1.000000,1.300000), Hit Points: 110\n   (C) Name: Lavender, Position: (2.250000,2.000000), Hit Points: 110\n   (C) Name: Fred, Position: (8.200000,9.100000), Hit Points: 110\n   (C) Name: George, Position: (0.000000,2.125000), Hit Points: 110\n   (N) Name: Hermione, Position: (1.220000,3.000000), Hit Points: 100\n   (N) Name: Luna, Position: (1.500000,0.250000), Hit Points: 120\n   (N) Name: Ginny, Position: (4.250000,9.100000), Hit Points: 100\n   (N) Name: Sirius, Position: (7.050000,3.500000), Hit Points: 150\n";
        CHECK(out.str() == expected_out);
    }
}

TEST_CASE("Team attack") {
    // Creat team1
    Cowboy* cowboy1 = new Cowboy("Harry", Point(1.0, 1.0));
    Cowboy* cowboy2 = new Cowboy("Ron", Point(2.125, 2.5));
    TrainedNinja* ninja1 = new TrainedNinja("Hermione", Point(1.22, 3.0));
    YoungNinja* ninja2 = new YoungNinja("Ginny", Point(4.25, 9.1));
    OldNinja* ninja3 = new OldNinja("Neville", Point(7.05, 3.5));

    Team team1(cowboy1);
    team1.add(cowboy2);
    team1.add(ninja1);
    team1.add(ninja2);
    team1.add(ninja3);

    // Create team 2
    Cowboy* cowboy12 = new Cowboy("Draco", Point(1.5, -7.0));
    Cowboy* cowboy22 = new Cowboy("Snape", Point(1.5, 1.125));
    OldNinja* ninja12 = new OldNinja("Bellatrix", Point(1.5, 1.125));
    YoungNinja* ninja22 = new YoungNinja("Lucius", Point(1.5, 0.75));

    Team team2(cowboy12);
    team2.add(cowboy22);
    team2.add(ninja12);
    team2.add(ninja22);

    SUBCASE("Attacking with living members") {
        // Attack team2 with team1
        team1.attack(&team2);

        // Check if expected number of team members are alive after the attack
        CHECK(team1.stillAlive() == 5);
        CHECK(team2.stillAlive() == 4);

        CHECK(cowboy22->getHitPoints() == 90); // cowboy22 is the closest alive player to team1 leader 

        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);

        CHECK(team1.stillAlive() == 5);
        CHECK(team2.stillAlive() == 3);

        // cowboy22 is the closest alive player to team1 leader 
        CHECK(cowboy22->getHitPoints() == 0);
        CHECK_FALSE(cowboy22->isAlive()); 

        team1.attack(&team2);
        CHECK(ninja12->getHitPoints() == 140); // ninja12 is the closest alive player to team1 leader 
    }

    SUBCASE("Team attack self") {
        CHECK_THROWS(team1.attack(&team1));
    }

    SUBCASE("Print team after attack and death"){
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);

        // Redirect cout to stringstream
        std::stringstream out;
        std::streambuf* cout_buf = std::cout.rdbuf();
        std::cout.rdbuf(out.rdbuf());

        team2.print();

        std::cout.rdbuf(cout_buf);

        std::string expected_out = "Team members:\n   (C) Name: Draco, Position: (1.500000,-7.000000), Hit Points: 110\n   (C) Name: (Snape), Position: (1.500000,1.125000)\n   (N) Name: Bellatrix, Position: (1.500000,1.125000), Hit Points: 140\n   (N) Name: Lucius, Position: (1.500000,0.750000), Hit Points: 100\n";
        CHECK(out.str() == expected_out);
    }

    SUBCASE("Leader changes when dead"){
        CHECK_EQ(team1.getLeader()->getName(), "Harry");
        team2.attack(&team1);
        team2.attack(&team1);
        team2.attack(&team1);
        team2.attack(&team1);
        team2.attack(&team1);
        team2.attack(&team1);
        team2.attack(&team1);

        CHECK_FALSE(cowboy1->isAlive());

        team1.attack(&team2);
        CHECK_EQ(team1.getLeader()->getName(), "Ron");
    }
}

TEST_CASE("Team2 initialization") {
    Cowboy* cowboy1 = new Cowboy("Harry", Point(1.0, 1.0));
    Cowboy* cowboy2 = new Cowboy("Ron", Point(2.125, 2.5));
    Cowboy* cowboy3 = new Cowboy("Neville", Point(1.0, 1.3));
    Cowboy* cowboy4 = new Cowboy("Lavender", Point(2.25, 2.0));
    Cowboy* cowboy5 = new Cowboy("Fred", Point(8.2, 9.1));
    YoungNinja* ninja1 = new YoungNinja("Hermione", Point(1.22, 3.0));
    TrainedNinja* ninja2 = new TrainedNinja("Luna", Point(1.5, 0.25));
    YoungNinja* ninja3 = new YoungNinja("Ginny", Point(4.25, 9.1));
    TrainedNinja* ninja4 = new TrainedNinja("Seamus", Point(3.0, 3.0));

    Team2 team1(cowboy1);
    CHECK(team1.stillAlive() == 1);

    CHECK_NOTHROW(team1.add(cowboy2));
    CHECK_NOTHROW(team1.add(ninja1));
    CHECK_NOTHROW(team1.add(ninja2));
    CHECK_NOTHROW(team1.add(cowboy3));
    CHECK_NOTHROW(team1.add(cowboy4));
    CHECK_NOTHROW(team1.add(ninja3));
    CHECK_NOTHROW(team1.add(new OldNinja("Sirius", Point(7.05, 3.5))));
    CHECK_NOTHROW(team1.add(cowboy5));
    CHECK_NOTHROW(team1.add(new Cowboy("George", Point(0.0, 2.125))));

    CHECK(team1.stillAlive() == 10);

    SUBCASE("Check leader") {
        CHECK_EQ(team1.getLeader()->getName(), "Harry");
    }
    
    SUBCASE("Adding too many characters") {
        CHECK_THROWS(team1.add(ninja4));
    }

    SUBCASE("Adding member of another team"){
        TrainedNinja* ninja21 = new TrainedNinja("Seamus", Point(3.0, 3.0));
        Team2 team2(ninja21);
        CHECK_THROWS(team1.add(ninja21));
    }

    SUBCASE("Print team"){
        // Redirect cout to stringstream
        std::stringstream out;
        std::streambuf* cout_buf = std::cout.rdbuf();
        std::cout.rdbuf(out.rdbuf());

        team1.print();

        std::cout.rdbuf(cout_buf);

        std::string expected_out = "Team members:\n   (C) Name: Harry, Position: (1.000000,1.000000), Hit Points: 110\n   (C) Name: Ron, Position: (2.125000,2.500000), Hit Points: 110\n   (N) Name: Hermione, Position: (1.220000,3.000000), Hit Points: 100\n   (N) Name: Luna, Position: (1.500000,0.250000), Hit Points: 120\n   (C) Name: Neville, Position: (1.000000,1.300000), Hit Points: 110\n   (C) Name: Lavender, Position: (2.250000,2.000000), Hit Points: 110\n   (N) Name: Ginny, Position: (4.250000,9.100000), Hit Points: 100\n   (N) Name: Sirius, Position: (7.050000,3.500000), Hit Points: 150\n   (C) Name: Fred, Position: (8.200000,9.100000), Hit Points: 110\n   (C) Name: George, Position: (0.000000,2.125000), Hit Points: 110\n";
        CHECK(out.str() == expected_out);
    }
}

TEST_CASE("Team2 attack") {
    // Create team1
    Cowboy* cowboy1 = new Cowboy("Harry", Point(1.0, 1.0));
    Cowboy* cowboy2 = new Cowboy("Ron", Point(2.125, 2.5));
    TrainedNinja* ninja1 = new TrainedNinja("Hermione", Point(1.22, 3.0));
    YoungNinja* ninja2 = new YoungNinja("Ginny", Point(4.25, 9.1));
    OldNinja* ninja3 = new OldNinja("Neville", Point(7.05, 3.5));

    Team2 team1(cowboy1);
    team1.add(cowboy2);
    team1.add(ninja1);
    team1.add(ninja2);
    team1.add(ninja3);

    // Create team 2
    Cowboy* cowboy12 = new Cowboy("Draco", Point(1.5, -7.0));
    Cowboy* cowboy22 = new Cowboy("Snape", Point(1.5, 1.125));
    OldNinja* ninja12 = new OldNinja("Bellatrix", Point(1.5, 1.125));
    YoungNinja* ninja22 = new YoungNinja("Lucius", Point(1.5, 0.75));

    Team2 team2(cowboy12);
    team2.add(cowboy22);
    team2.add(ninja12);
    team2.add(ninja22);

    SUBCASE("Attacking with living members") {
        // Attack team2 with team1
        team1.attack(&team2);

        // Check if expected number of team members are alive after the attack
        CHECK(team1.stillAlive() == 5);
        CHECK(team2.stillAlive() == 4);

        CHECK(cowboy22->getHitPoints() == 90); // cowboy22 is the closest alive player to team1 leader 

        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);

        CHECK(team1.stillAlive() == 5);
        CHECK(team2.stillAlive() == 3);

        // cowboy22 is the closest alive player to team1 leader 
        CHECK(cowboy22->getHitPoints() == 0);
        CHECK_FALSE(cowboy22->isAlive()); 

        team1.attack(&team2);
        CHECK(ninja12->getHitPoints() == 140); // ninja12 is the closest alive player to team1 leader 
    }

    SUBCASE("Team attack self") {
        CHECK_THROWS(team1.attack(&team1));
    }

    SUBCASE("Print team after attack and death"){
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);
        team1.attack(&team2);

        // Redirect cout to stringstream
        std::stringstream out;
        std::streambuf* cout_buf = std::cout.rdbuf();
        std::cout.rdbuf(out.rdbuf());

        team2.print();

        std::cout.rdbuf(cout_buf);

        std::string expected_out = "Team members:\n   (C) Name: Draco, Position: (1.500000,-7.000000), Hit Points: 110\n   (C) Name: (Snape), Position: (1.500000,1.125000)\n   (N) Name: Bellatrix, Position: (1.500000,1.125000), Hit Points: 140\n   (N) Name: Lucius, Position: (1.500000,0.750000), Hit Points: 100\n";
        CHECK(out.str() == expected_out);
    }

    SUBCASE("Leader changes when dead"){
        CHECK_EQ(team1.getLeader()->getName(), "Harry");
        team2.attack(&team1);
        team2.attack(&team1);
        team2.attack(&team1);
        team2.attack(&team1);
        team2.attack(&team1);
        team2.attack(&team1);
        team2.attack(&team1);

        CHECK_FALSE(cowboy1->isAlive());

        team1.attack(&team2);
        CHECK_EQ(team1.getLeader()->getName(), "Ron");
    }
}

