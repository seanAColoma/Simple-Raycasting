#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
    public:
        double min, max;
        //default empty list
        interval() : min(+infinity), max(-infinity) {}
        interval(double min, double max) : min(min), max(max) {}

        double size() {
            return max-min;
        }

        //return x element [min, max] - inclusive
        bool contains(double x) {
            return ((min <= x) && (x <= max)); 
        }
        //return x element (min, max) - non inclusive
        bool surrounds(double x) {
            return ((min < x) && (x < max));
        }

        static const interval empty, universe;

        double clamp(double x) const {
            if(x<min) {
                return min;
            }
            if(x>max) {
                return max;
            }
            return x;
        }
};

//empty interval is returned by default
const interval interval::empty = interval(+infinity, infinity);

//interval of all values
const interval interval::universe = interval(-infinity, infinity);

#endif