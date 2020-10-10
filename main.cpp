// main file - main.cpp
/*
Full name: Ariel Gutierrez
Student ID: 2318163
Chapman email: arigutierrez@chapman.edu
Course number and section: CPSC 350-01
Assignment or exercise number: Assignment 2

Assignment 2: Program that implements the Game of Life, a simulation that models
the life cycle of bacteria.
*/

#include "assign2.h"

int main(int argc, char** argv){
  string userInput;
  int dimensions[2];
  string filePath;
  while(true){
    cout << "Would you like to provide a \"mapfile\" of the world where the " << endl;
    cout << "simulation would be carried out, or would you like a \"random\" " << endl;
    cout << "assignment?" << endl;
    userInput = "";
    cin >> userInput;
    for(int i = 0; i < userInput.length(); ++i){
      userInput[i] = tolower(userInput[i]); //make lowercase
    }
    if(userInput == "random"){
      cout << "What are the dimensions of the world? " << endl;
      dimensions[0] = GameOfLife::getUserDim("first");
      dimensions[1] = GameOfLife::getUserDim("second");
      break;
    }else if(userInput == "mapfile"){
      filePath = GameOfLife::getMapFile(dimensions);
      break;
    }else{
      cout << "Invalid input. Try again." << endl;
    }
    cout << endl;
  }

  GameOfLife *gof = new GameOfLife(dimensions[0],dimensions[1]);
  if(userInput == "random"){
    double popDense = GameOfLife::getUserDensity();
    gof->randomAssignment(popDense);
  }else if(userInput == "mapfile"){
    gof->copyConfiguration(filePath);
  }

  gof->chooseGameMode();
  gof->viewSimulation(); //Prompts user for what way they want to view simulation
  gof->simulation();

  delete gof;
  return 0;
}
