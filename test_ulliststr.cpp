#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "ulliststr.h"
using namespace std;

//Use this file to test your ulliststr implementation before running the test suite

int main(int argc, char* argv[])
{
  // test below is directly from writeup
  ULListStr dat;
  dat.push_back("7");
  dat.push_front("8");
  dat.push_back("9");
  cout << dat.get(0) << " " << dat.get(1) << " " << dat.get(2) << endl;
  // prints: 8 7 9
  cout << dat.size() << endl;  // prints 3 since there are 3 strings stored
  
  ULListStr dat2;
  dat2.push_back("5");
  dat2.push_front("6");
  cout << dat2.get(0) << " " << dat2.get(1) << endl;

  ULListStr list;
	list.push_front("fred");
	list.push_back("bob");
  cout << list.get(0) << " " << list.get(1) << endl;


  return 0;
}
