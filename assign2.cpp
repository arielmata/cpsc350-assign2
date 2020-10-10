// implementation file - assign2.cpp
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

GameOfLife::GameOfLife(int d1, int d2){
  myMatrix = new char*[d1];
  myCopy = new char*[d1];
  for(int i = 0; i < d1; ++i){
    myMatrix[i] = new char[d2];
    myCopy[i] = new char[d2];
  }
  generation = 0;
  dim1 = d1;
  dim2 = d2;
  gameMode = "";
  viewSim = "";
  outputFile = "";
}

GameOfLife::~GameOfLife(){
  for(int i = 0; i < dim1; ++i) {
    delete [] myMatrix[i];
    delete [] myCopy[i];
  }
  delete [] myMatrix;
  delete [] myCopy;
}

//Given two int values i,j, which is a cell in a matrix, and the copy array,
//we find the number of neighbors in accordance to classic mode
int GameOfLife::classicNeighbors(int i, int j){
  int n = 0;
  for(int x = i-1; x <= i+1; ++x){
    for(int y = j-1; y <= j+1; ++y){
      if(x < 0 || y < 0 || x >= dim1 || y >= dim1 || (x == i && y == j)){
          continue; // don't count itself or cells that don't exist
      }else if(myCopy[x][y] == 'X'){
        ++n; //cell has neighbor
      }
    }
  }
  return n;
}

//Given two int values i,j, which is a cell in a matrix, and the copy array,
//we find the number of neighbors in accordance to doughnut mode
int GameOfLife::doughnutNeighbors(int i, int j){
  int n = 0;
  for(int x = i-1; x <= i+1; ++x){
    for(int y = j-1; y <= j+1; ++y){
      if(x == i && y == j){
        continue; //we don't count itself as neighbor
      }else if((x == -1 && y == -1) || (x == dim1 && y == -1)
        || (x == -1 && y == dim2) || (x == dim1 && y == dim2)){
        int xNew = x;
        int yNew = y;
        if(x == -1){
          xNew = dim1 - 1;
        }else{
          xNew = 0;
        }
        if(y == -1){
          yNew = dim2 - 1;
        }else{
          yNew = 0;
        }
        if(myCopy[xNew][yNew] == 'X'){
          ++n;
        }
      }else if(x < 0){
        if(myCopy[dim1-1][y]=='X'){
          ++n;
        }
      }else if(y < 0){
        if(myCopy[x][dim2-1]=='X'){
          ++n;
        }
      }else if(x >= dim1){
        if(myCopy[0][y]=='X'){
          ++n;
        }
      }else if (y >= dim2){
        if(myCopy[x][0]=='X'){
          ++n;
        }
      }else if(myCopy[x][y] == 'X'){
        ++n; //cell has neighbor
      }
    }
  }
  return n;
}

//Given two int values i,j (a cell in a matrix), returns the number of
//neighbors for that cell.
int GameOfLife::mirrorNeighbors(int i, int j){
  int n = 0;
  for(int x = i-1; x <= i+1; ++x){
    for(int y = j-1; y <= j+1; ++y){
      if(x==i && y==j){
        continue;
      }else if((x == -1 && y == -1) || (x == dim1 && y == -1) ||
        (x == -1 && y == dim2) || (x == dim1 && y == dim2)){
          if(myCopy[i][j] == 'X'){
            ++n;
          }
      }else if(y < 0){
        if(myCopy[x][0]=='X')
          ++n;
      }else if(x < 0){
        if(myCopy[0][y]=='X')
          ++n;
      }else if(y == dim2){
        if(myCopy[x][dim2-1]=='X')
          ++n;
      }else if(x == dim1){
        if(myCopy[dim1-1][y]=='X')
          ++n;
      }else if(myCopy[x][y] == 'X'){
        ++n;
      }
    }
  }
  return n;
}

//Carries out the simulation for the game. If the world becomes empty, it asks
//the user to press "enter" key to quit, otherwise it keeps running if infinite.
void GameOfLife::simulation(){
  int n;
  string userInput = "";
  getline(cin, userInput);
  while(!isMatrixEmpty()){
    ++generation;
    copyMatrix();
    if(viewSim == "pause"){
      printMatrix();
      sleep(1);
    }else if(viewSim == "enter"){
      printMatrix();
      string userInput = "";
      do{
        cout << "Press ENTER key to continue" << endl;
        getline(cin, userInput);
      }while(userInput.length() != 0);
    }else if(viewSim == "file"){
      ofstream outfile;
      outfile.open(outputFile, std::fstream::out | std::fstream::app);
      printMatrixFile(outfile);
      outfile.close();
    }

    for(int i = 0; i < dim1; ++i){
      for(int j = 0; j < dim2; ++j){
        if(gameMode == "classic"){
          n = classicNeighbors(i,j);
        }else if (gameMode == "doughnut"){
          n = doughnutNeighbors(i,j);
        }else if(gameMode == "mirror"){
          n = mirrorNeighbors(i,j);
        }
        //now with neighbor count we update the cell in myMatrix
        if(n <= 1){
          myMatrix[i][j] = '-';
        }else if(n == 2){
          continue;
        }else if(n == 3){
          myMatrix[i][j] = 'X';
        }else{
          myMatrix[i][j] = '-';
        }
      }
    }
  }

  userInput = "";
  do{
    cout << "The world is now empty. Press ENTER key to exit the program" << endl;
    getline(cin, userInput);
  }while(userInput.length() != 0);
  cout << "Farewell." << endl;
}

//Randomly generate the initial cell configuration using the dimension
//and density inputs for random assignment
void GameOfLife::randomAssignment(double popDensity){
  for(int i = 0; i < dim1; ++i){
    for(int j = 0; j < dim2; ++j){
      myMatrix[i][j] = '-';
    }
  }

  int cellsFilled = 0;
  int cellsNeeded = (int)(popDensity*dim1*dim2);
  int x,y;
  srand(time(NULL));
  while(cellsFilled != cellsNeeded){
    x = rand() % dim1;
    y = rand() % dim2;

    if(myMatrix[x][y] == '-'){
      myMatrix[x][y] = 'X';
      ++cellsFilled;
    }
  }
}

//Makes the contents of myCopy equal to myMatrix
void GameOfLife::copyMatrix(){
  for(int i = 0; i < dim1; ++i){
    for(int j = 0; j < dim2; ++j){
      myCopy[i][j] = myMatrix[i][j];
    }
  }
}

//Prints myMatrix to standard output
void GameOfLife::printMatrix(){
  cout << "Generation: " << generation << endl;
  for(int i = 0; i < dim1; ++i){
    for (int j = 0; j < dim2; ++j){
      cout << myMatrix[i][j];
    }
    cout << endl;
  }
}

//Prints myMatrix to an output file
void GameOfLife::printMatrixFile(ofstream& ofs){
  ofs << "Generation: " << generation << endl;
  for(int i = 0; i < dim1; ++i){
    for (int j = 0; j < dim2; ++j){
      ofs << myMatrix[i][j];
    }
    ofs << endl;
  }
}

//Returns true if a string can be converted to an int value, false otherwise
bool GameOfLife::isInteger(string s){
  bool isInt = true;
  for(int i = 0; i < s.length(); ++i){
    if((int)s[i] < 48  || (int)s[i] > 57){
      isInt = false;
    }
  }
  return isInt;
}

//Returns true if a string can be converted to a decimal that is less than 1
bool GameOfLife::isDecimalLess1(string s){
  bool isDec = false;
  if(((s.find(".") != string::npos) && (s.substr(0,s.find(".")) == "0"))
    || s.find(".") == 0){
    if(isInteger(s.substr(s.find(".") + 1)))
      isDec = true;
  }
  return isDec;
}

//Returns true if the matrix is empty, otherwise returns false
bool GameOfLife::isMatrixEmpty(){
  bool isEmpty = true;
  for(int i = 0; i < dim1; ++i){
    for(int j = 0; j < dim2; ++j){
      if(myMatrix[i][j]=='X')
        isEmpty = false;
    }
  }
  return isEmpty;
}

//Prompts the user for a dimension and returns the dimension as an int.
int GameOfLife::getUserDim(string s){
  int dim;

  while(true){
    cout << "Please input the " << s << " dimension of the world: ";
    string userDim = "";
    cin >> userDim;
    if(isInteger(userDim)){
      stringstream ss(userDim);
      ss >> dim;
      break;
    }else{
      cout << "Invalid dimension." << endl;
    }
    cout << endl;
  }
  return dim;
}

//Prompt the user for a population density between 0 and 1, and returns it as
//a double.
double GameOfLife::getUserDensity(){
  double pd;
  while(true){
    cout << "Please input a decimal value greater than 0 and less than 1: " << endl;
    string userDense = "";
    cin >> userDense;

    if(isDecimalLess1(userDense)){
      pd = stod(userDense);
      break;
    }else{
      cout << "Invalid input. Input was not a proper decimal. " << endl;
    }
    cout << endl;
  }
}

//Prompts user for mapfile and checks if it has the right configuration
string GameOfLife::getMapFile(int arr[]){
  bool isCorrectFile = false;
  string line;
  string filePath;
  while(!isCorrectFile){
    cout << "Please type the file path to the mapfile: " << endl;
    cin >> filePath;
    ifstream f;
    f.open(filePath);
    if(f.fail()){
      cout << "Invalid file path." << endl;
    }else{
      isCorrectFile = true;
      int lineCount = 0;
      int d1, d2;
      while(getline(f,line)){
        line.erase(line.length()-1); //delete new line char
        if(lineCount == 0){
          string userD1 = line;
          if(isInteger(userD1)){
            stringstream ss1(userD1);
            ss1 >> d1;
            arr[0] = d1;
          }else{
            isCorrectFile = false;
            break;
          }
        }else if(lineCount == 1){
          string userD2 = line;
          if(isInteger(userD2)){
            stringstream ss2(userD2);
            ss2 >> d2;
            arr[1] = d2;
          }else{
            isCorrectFile = false;
            break;
          }
        }else if(lineCount > d1 + 1){
          continue;
        }
        else{
          if(d2 != line.length()){
            isCorrectFile = false;
            break;
          }
          for(int i = 0; i < line.length(); ++i){
            if(line[i] != 'X' && line[i] != '-'){
              isCorrectFile = false;
              break;
            }
          }
        }
        ++lineCount;
      }
      f.close();
      if(!isCorrectFile){
        cout << "Invalid File Configuration." << endl;
      }
    }
    cout << endl;
  }
  return filePath;
}

//Given a proper filepath, the function copies the configuration onto myMatrix
void GameOfLife::copyConfiguration(string filePath){
  string line;
  int lineCount = -1;
  int iCount = 0;
  ifstream fp;
  fp.open(filePath);

  while(getline(fp,line)){
    ++lineCount;
    if(lineCount <= 1 || lineCount > dim1 + 1){
      continue;
    }else{
      for(int i = 0; i < dim2; ++i){
        if(line[i] != 'X' && line[i] != '-'){
          continue;
        }
        myMatrix[iCount][i] = line[i];
      }
      ++iCount;
    }
  }
  fp.close();
}

//Prompts user for how they want to view the simulation. Either a brief "pause",
//press "enter" key, or if they want to output to a file.
void GameOfLife::viewSimulation(){
  while(true){
    viewSim = "";
    cout << "Do you want a brief \"pause\" between generations, press \"enter\" " << endl;
    cout << "to display the next generation, or output everything to a \"file\" " << endl;
    cin >> viewSim;
    cout << endl;
    if(viewSim == "pause" || viewSim == "enter"){
      break;
    }else if(viewSim == "file"){
      cout << "What is the file that you would like to output to? " << endl;
      cin >> outputFile;
      break;
    }else{
      cout << "Invalid input. Please try again." << endl;
    }
    cout << endl;
  }
}

//Prompts the user for the game mode they would like to run in
void GameOfLife::chooseGameMode(){
  while(true){
    string userInput = "";
    cout << "Which is the game mode you would like to run? (classic/doughnut/mirror)" << endl;
    cin >> userInput;

    for(int i = 0; i < userInput.length(); ++i){
      userInput[i] = tolower(userInput[i]); //make input all lower case
    }

    if(userInput == "classic" || userInput == "doughnut" || userInput == "mirror"){
      gameMode = userInput;
      break;
    }else{
      cout << "Invalid input. Please try again." << endl;
    }
    cout << endl;
  }
}
