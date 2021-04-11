#include "automata.h"
#include <iostream>
//#include <cstdlib>
#include <time.h>

#define ALIVE_CHAR '#'
#define DEAD_CHAR '.'

using std::cout;

namespace automata {

    population::population(int l, int w) { // default population constructor
        width = (w >= 3) ? w : 3;
        length = (l >= 3) ? l : 3;

        individuals = new specimen*[l];
        for (int i = 0; i < l; ++i) {
            individuals[i] = new specimen[w];
        }

    }

    void population::print() { //print a population grid
        for(int row = 0; row < length; row++) {
            for (int column = 0; column < width; column++) {
                cout << "" << individuals[row][column];
            }
            cout << "\n";
        }
        cout << std::flush;
    }

    std::ostream&  operator<<(std::ostream& outs, specimen& source) { // single specimen output
        int s = source.getState();
        char visual_state;

        switch (s) {
            case 1:
                visual_state = ALIVE_CHAR; // alive
                break;
            default:
            case 0:
                visual_state = DEAD_CHAR; // dead
                break;
        }

        outs << " " << visual_state << "";

        return outs;
    }

    void population::randInit(int a) { // Initialize a population randomly with 1:a ratio
        srand(time(NULL));
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < length; j++) {
                individuals[i][j].setState(rand() % (a+1) ); // means 1:a dead:alive
                if (individuals[i][j].getState() != 1)
                    individuals[i][j].setState(0);
            }
        }
    }

    int population::countNeighbourhood(int row, int column) { // count the total value of the neighborhood for given index
        unsigned int count = (individuals[row][column].getState() == 1) ? -1 : 0;
        int comprow = row, compcol = column;

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                comprow = row+i;
                compcol = column+j;

                if (comprow == -1)
                    comprow = width-1;
                else if (comprow == width)
                    comprow = 0;
                if (compcol == -1)
                    compcol = length-1;
                else if (compcol == length)
                    compcol = 0;

                count += individuals[comprow][compcol].getState();
            }
        }
        return count;
    }

    population population::nextPopulation() {
        population next(width,length);
        int neighbours;
        int countNeighbourhood(int, int);
        specimen::value_type nextState(specimen&, int);

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < length; j++) {
                neighbours = this->countNeighbourhood(i,j);
                next.individuals[i][j] = nextState(individuals[i][j],neighbours);
            }
        }

        return next;
    }

    // only visible inside nextPopulation()
    specimen::value_type nextState(specimen& istance, int neighbours) { // returns what the next state should be for a cell given the current state and neighbourhood
        specimen::value_type nextState = 0;
        specimen::value_type state = istance.getState();

        if (neighbours == 3)
            nextState = 1;
        else if (neighbours == 2)
            nextState = (state == 1) ? 1 : 0;
        else
            nextState = 0;

        return nextState;
    }



}