#include <iostream>
#include <unistd.h>
#include <ctime>

#include "automata.h"

using namespace automata;
using std::cout;
using std::stoi;

#define DEFAULT_SIZE 3
#define DEFAULT_RATIO 5
#define DEFAULT_ITERAIONS 200 // 1 minute with default delay
#define DEFAULT_DELAY 0.3 // in seconds

void wait(float);
void clear();
void printHelp();

int main (int argc, char* const* argv) {
    int rows = DEFAULT_SIZE, columns = DEFAULT_SIZE, ratio = DEFAULT_RATIO, iterations = DEFAULT_ITERAIONS, opt;
    float delay = DEFAULT_DELAY;

    while( ( opt = getopt(argc, argv, "hr:d:c:k:i:") ) != -1 ) { // options parse
        switch(opt) {
                case 'r':
                    rows = stoi(optarg);
                    break;
                case 'c':
                    columns = stoi(optarg);
                    break;
                case 'k':
                    ratio = stoi(optarg);
                    break;
                case 'i':
                    iterations = stoi(optarg);
                    break;
                case 'd':
                    delay = atof(optarg);
                    break;
                case 'h':
                case '?':
                    printHelp();
                    exit(0);
                default:
                    abort();
        }
    }


    population city(rows,columns);  // generate and
    city.randInit(ratio);           // initialize the city

    clear(); // clear output
    city.print(); // print initialized city
    cout << "\nPress enter to start.";
    getchar(); // wait for enter
    city = city.nextPopulation(); // pre-calculate first iteration
    while(true) {
        for (int i = 0; i < iterations; i++) {
            clear();
            cout << std::endl;
            city.print();
            city = city.nextPopulation(); // pre-calculate next iteration
            wait(delay);
        }
        cout << "\nPress enter to continue.";
        getchar();
    }


    return 0;
}

void wait(float delay) {
    clock_t start = clock();
    while( (clock() - start) < delay*CLOCKS_PER_SEC ) {}
}

void clear() {
    #if defined _WIN32
        //system("cls");
        #include <conio.h>
        clrscr(); // including header file : conio.h
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined (__APPLE__)
        //system("clear");
        std::cout<< "\x1B[2J\x1B[H"; //Using ANSI Escape Sequences
    #endif
}

void printHelp() {
    cout << " Game of Life\n\n";

    cout << " Parameters:\n";
    cout << "\t-r [N]\t–\tCreate a grid with [N] rows (min and default is 3)\n";
    cout << "\t-c [N]\t–\tCreate a grid with [N] columns (min and default is 3)\n";
    cout << "\t-k [N]\t–\tSets the initialization dead:alive ratio as [N]:1\n";
    cout << "\t-i [N]\t–\tIterate [N] times before stopping\n";
    cout << "\t-d [D]\t–\tsets the delay between iterations in seconds (can use decimal)\n";
    cout << "\t-h\t–\tDisplay this help message\n";
}