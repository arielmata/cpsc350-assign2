// header file - assign2.h
/*
Full name: Ariel Gutierrez
Student ID: 2318163
Chapman email: arigutierrez@chapman.edu
Course number and section: CPSC 350-01
Assignment or exercise number: Assignment 2

Assignment 2: Program that implements the Game of Life, a simulation that
models the life cycle of bacteria.
*/

#include <iostream> //input and output
#include <fstream> //read and open files
#include <stdlib.h> //srand, rand, RAND_MAX
#include <sstream> //stringstream
#include <ctime> //current time function
#include <unistd.h> //sleep function
using namespace std;

class GameOfLife{
  public:
    GameOfLife(int d1, int d2); //default constructor
    ~GameOfLife(); //destructor

    //game modes
    int classicNeighbors(int i, int j);
    int doughnutNeighbors(int i, int j);
    int mirrorNeighbors(int i, int j);

    //functions
    void simulation();
    void randomAssignment(double popDensity);

    //helper functions
    void copyMatrix();
    void printMatrix();
    void printMatrixFile(ofstream& ofs);
    static bool isInteger(string s);
    static bool isDecimalLess1(string s);
    bool isMatrixEmpty();
    static int getUserDim(string s);
    static double getUserDensity();
    static string getMapFile(int arr[]);
    void copyConfiguration(string fp);
    void viewSimulation();
    void chooseGameMode();
  private:
    char **myMatrix;
    char **myCopy;
    int generation;
    int dim1;
    int dim2;
    string gameMode;
    string viewSim;
    string outputFile;
};
