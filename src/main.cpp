#include <iostream>
#include "CoordMatrix.h"
#include "Tour.h"
#include "TSPalgorithm.h"

using namespace std;
int main() {

  TSPalgorithm test;
    
 // test.CreateTestSolution();
 test.CreateSolution();
  test.Optimize();

    
}