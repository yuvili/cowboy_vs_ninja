#ifndef POINT_HPP
#define POINT_HPP

class Point{
    private:
        double x, y;
    
    public:
        Point(){}
        Point(double, double){}// check overflow of double? when reciev float??
        ~Point(){} // Destructor
        Point(const Point& other){} // Copy constructor
        Point(Point&& other) noexcept{} // Move constructor

        double distance(Point&);
        void print();
        Point& moveTowards(Point&, Point&, double);
        double getX();
        double getY();
};
#endif