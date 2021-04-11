#ifndef CELLULAR_AUTOMATA_H
#define CELLULAR_AUTOMATA_H

#include <iostream>

namespace automata {
    class specimen {
        public:
            typedef unsigned int value_type;

            specimen(int value = 0) { setState(value); }; // default specimen constructor

            void setState(const value_type x) { state = x; };
            value_type getState() const { return state; };

        private:
            value_type state;
    };

    class population {
        public:
            typedef int size_type;

            population(int = 2, int = 1);

            void randInit( int = 6 ); // Initialize a population randomly with 1:a ratio, default is 6
            void print();
            population nextPopulation(); // Compute the next state for the whole population and return
            int countNeighbourhood(int, int);

        private:
            size_type length;
            size_type width;
            specimen** individuals;
    };

    std::ostream& operator<< (std::ostream&, specimen&);
}

#endif