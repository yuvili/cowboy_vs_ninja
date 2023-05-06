#ifndef POINT_HPP
#define POINT_HPP

class Point{
    private:
        double _x, _y;
    
    public:
        Point();
        Point(double, double);
        ~Point(); // Destructor
        Point(const Point& other); // Copy constructor
        Point(Point&& other) noexcept; // Move constructor

        Point& operator=(const Point&);

        double distance(Point&);
        void print();
        Point moveTowards(Point&, Point&, double);
        double getX();
        double getY();
};
#endif