#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

/* 
 * sysgen.cpp
 * Russell Gavin Fielder
 * 4/12/2017 v2
 * 
 * This program generates 2-dimensional linear homogenous systems of differential equations of various behaviors
 * 
 * copyright 2017 Gavin Fielder
 * free to use and distrubute among CSU Chico Students/Faculty
 */


class matrix_2x2 {
  public:    // configuration:
    int a;        //   a  b
    int b;        //   c  d
    int c;
    int d;
    void resolve(int D, int T);
    void print();
    matrix_2x2(string myName = "A");
    string name;
    string behavior;
};

//function prototypes
void generateMatrix(int, matrix_2x2&);
void factorMe(int, int&, int&);
bool flipACoin();
void swap2(int&, int&);
bool isPerfectSquare(int discrim, bool negative = false);
int discriminant(int, int);
int getRandom(int);
void printSettings();

// general use array for different behavior descriptions -- do not reorder
const string behaviorStrings[] = {
      "stable node integer",
      "stable node irrational",
      "unstable node integer",
      "unstable node irrational",
      "saddle integer",
      "saddle irrational",
      "stable spiral integer",
      "stable spiral irrational",
      "unstable spiral integer",
      "unstable spiral irrational",
      "repeated eigenvalues stable integer",
      "repeated eigenvalues unstable integer",
      "one eigenvalue is 0, unstable equilibria",
      "one eigenvalue is 0, stable equilibria",
      "center" 
};

// global array of bools for selecting which behavior types to generate
bool programSettings[15] = {true, true, true, true, true, true, true, true, true, true, true, true, true, true,true};


// main program
int main() {
  srand(time(NULL));
  int userChoice = 0;
  char userChar;
  int randomNumber = 0;
  matrix_2x2 newMatrix;
  vector<matrix_2x2> matrices; // vector of matrices
  bool quit = false;

  cout << "Welcome to the Linear Homogenous 2x2 System of Differential Equations Generator" << endl;
  // main program loop
  do {
    cout << "===== Main Menu =====" << endl;
    cout << "  Enter 1 to generate matrices" << endl;
    cout << "  Enter 2 to select possible system behaviors (default is all possible behaviors)" << endl;
    cout << "  Enter 3 (or anything else) to quit" << endl;
    cin >> userChoice;
    
    // generate matrices
    if (userChoice == 1) {
      cout << "How many matrices would you like to generate?" << endl;
      cin >> userChoice;
      matrices.clear();
      //populate vector with selected amount of matrices, use default constructor for each object
      matrices.assign(userChoice, matrix_2x2());
      cout << "For the 2x2 linear homogoneous system x'(t) = A * x(t), the matrix A is:" << endl;
      for (int i = 0; i < userChoice; i++) {
        //Generate a matrix out of the possible options
        do {
          randomNumber = getRandom(15) - 1;
        } while (!(programSettings[randomNumber]));
        generateMatrix(randomNumber, matrices[i]);
        matrices[i].name = "A" + to_string(i);
        matrices[i].print();
        cout << endl;
      }
      // ask if they want the behaviors printed
      cout << "Would you like to print the behaviors of these matrices? (y/n)" << endl;
      cin >> userChar;
      if ((userChar == 'y') || (userChar == 'Y')) {
        for (int i = 0; i < userChoice; i++) {
          cout << matrices.at(i).name << ": " << matrices[i].behavior << endl;
        } 
      }
      // end generate matrices
    }
    else if (userChoice == 2) {
      // settings loop
      do {
        printSettings();
        cout << "  Enter ##'s for behaviors you would like to switch on/off, separated by spaces," << endl;
        cout << "    enter -1 when done changing settings to return to the main menu." << endl;
        cin >> userChoice;
        if (userChoice != -1) {
          if (programSettings[userChoice] == true) programSettings[userChoice] = false;
          else programSettings[userChoice] = true;
        }
      } while (userChoice != -1);
    } 
    // if user selected anything other than 1 or 2 on main menu, quit
    else quit = true;
  } while (!(quit));

  return 0;
}

// This function generates a matrix of a selected behavior
void generateMatrix(int behaviorCode, matrix_2x2 & A) {
  string behaviorString = "";
  int T = 0;
  int D = 0;
  int x = 0;
  switch (behaviorCode + 1) {
    case 1: // stable node integer
      behaviorString = "stable node integer";
      do {
        do {
          T = -1 * (getRandom(8));
          D = (getRandom(8));
        } while (discriminant(T,D) < 0);
      } while (!(isPerfectSquare(discriminant(T,D))));
      break;

    case 2: // stable node irrational
      behaviorString = "stable node irrational";
      do {
        T = -1 * (getRandom(8));
        D = (getRandom(8));
      } while (discriminant(T,D) <= 0);
      break;

    case 3: // unstable node integer
      behaviorString = "unstable node integer";
      do {
        do {
          T = getRandom(8);
          D = getRandom(8);
        } while (discriminant(T,D) <= 0);
      } while (!(isPerfectSquare(discriminant(T,D))));
      break;

    case 4: // unstable node irrational
      behaviorString = "unstable node irrational";
      do {
        T = getRandom(8);
        D = getRandom(8);
      } while (discriminant(T,D) <= 0);
      break;

    case 5: // saddle integer
      behaviorString = "saddle integer";
      do {
        D = -1 * (getRandom(8));
        T = getRandom(14) - 7;
      } while (!(isPerfectSquare(discriminant(T,D))));
      break;

    case 6: // saddle irrational
      behaviorString = "saddle irrational";
      D = -1 * (getRandom(8));
      T = getRandom(14) - 7;
      break;
      
    case 7: // stable spiral integer
      behaviorString = "stable spiral integer";
      do {
        do {
          T = -1 * (getRandom(8));
          D = (getRandom(8));
        } while (discriminant(T,D) >= 0);
      } while (!(isPerfectSquare(discriminant(T,D),true)));
      break;

    case 8: // stable spiral irrational
      behaviorString = "stable spiral irrational";
      do {
        T = -1 * (getRandom(8));
        D = getRandom(8);
      } while (discriminant(T,D) >= 0);
      break;
      
    case 9: // unstable spiral integer
      behaviorString = "unstable spiral integer";
      do {
        do {
          T = getRandom(8);
          D = getRandom(8);
        } while (discriminant(T,D) > 0);
      } while (!(isPerfectSquare(discriminant(T,D), true)));
      break;
          
    case 10: // unstable spiral irrational
      behaviorString = "unstable spiral irrational";
      do {
        T = getRandom(8);
        D = getRandom(8);
      } while (discriminant(T,D) >= 0);
      break;

    case 11: // repeated eigenvalues stable integer
      behaviorString = "repeated eigenvalues stable integer";
      x = getRandom(4);
      T = -2 * x;
      D = x*x;
      break;

    case 12: // repeated eigenvalues unstable integer
      behaviorString = "repeated eigenvalues unstable integer";
      x = getRandom(4);
      T = 2 * x;
      D = x*x;
      break;
 
    case 13: // one eigenvalue is 0, unstable equilibria
      behaviorString = "one eigenvalue is 0, unstable equilibria";
      D = 0;
      T = getRandom(8);
      break;
 
    case 14: // one eigenvalue is 0, stable equilibria
      behaviorString = "one eigenvalue is 0, stable equilibria";
      D = 0;
      T = -1 * (getRandom(8));
      break;
    
    case 15:
      behaviorString = "center";
      do {
        T = 0;
        D = getRandom(8);
      } while (!(isPerfectSquare(4*D)));
      break;
  }
  
  // assign values of a, b, c, d in matrix A that  satisfies the selected parameters
  A.behavior = behaviorString;
  A.resolve(D, T);
}

// This function figures out a, b, c, d, for the given values of D and T
void matrix_2x2::resolve(int D, int T) {
  a = getRandom(10) - 5; // pick a random value for a
  d = T - a; // T = a + d
  factorMe((a*d - D), c, b); // D = ad-bc >> bc = ad-D; find integers c and b by finding two compatible integers that multiply to a*d - D
}

// This function prints the matrix name and values
void matrix_2x2::print() {
  cout << name << " =\t" << a << " \t" << b << endl;
  cout << "    \t" << c << " \t" << d << endl;
}

// Constructor for matrices
matrix_2x2::matrix_2x2(string myName) {
  name = myName;
  a = 0;
  b = 0;
  c = 0;
  d = 0;
}

// This function factors an integer into two (usually smaller) integers
void factorMe(int number, int& factor1, int& factor2) {
  factor1 = -1; //flag for not yet found
  factor2 = -1;
  if (number == 0) {
    factor1 = 1;
    factor2 = 0;
  }
  else if (number == 1) {
    factor1 = 1; 
    factor2 = 1;
  }
  else if (number == -1) {
    factor1 = 1;
    factor2 = -1;
  }
  else {
    int upper = number;
    if (upper < 0) upper *= -1;
    int i = 2;
    do {
      if ((number % i) == 0) {
        //found a factor
        factor1 = i;
        factor2 = (number / factor1);
      }
      i++;
    } while ((factor1 == -1) && (i <= upper));
  }
  //sometimes swap the two
  if (flipACoin()) swap2(factor1, factor2);
}


// This function randomly returns true or false
bool flipACoin() {
  int random = rand() % 2;
  return (random == 0);
}

// This function swaps two numbers
void swap2(int& num1, int& num2) {
  int temp = num1;
  num1 = num2;
  num2 = temp;
}

// This function returns a random integer from 1 to max
int getRandom(int max) {
  return ((rand() % max) + 1);
}

// This function checks if T^2 - 4D is a perfect square <= 100. If complex, pass true into the bool
bool isPerfectSquare(int discrim, bool negative) {
  bool valid = false;
  int i = 1;
  int mult = 1;
  if (negative) mult = -1;
  do {
    if (discrim == (mult * (i * i))) valid = true;
    i++;
  } while ((!(valid)) && (i <= 10));
  return valid;
}

// This function returns T^2 - 4D
int discriminant(int T, int D) {
  return ((T*T) - (4*D));
}


// Thus function prints the current settings
void printSettings() {
  cout << " === Program Settings === " << endl;
  for (int i = 0; i < 15; i++) {
    if (i < 10) cout << " ";
    cout << i << ":    ";
    if (programSettings[i]) cout << "[ACTIVE]  ";
    else cout << "[      ]  ";
    cout << behaviorStrings[i] << endl;
  }
  cout << endl;
}



















