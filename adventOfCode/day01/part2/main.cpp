#include <iostream>
#include <fstream>
using namespace std;
int main() {
  fstream inputfile;
  inputfile.open("input.txt", ios::in);
  if (inputfile.is_open()) {
    string curline;
    while (getline(inputfile, curline)) {
      cout << curline << endl;
    }
    inputfile.close();
  }
  return 0;
}