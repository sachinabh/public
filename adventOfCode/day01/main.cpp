#include <iostream>
#include <fstream>
using namespace std;
int main() {

  fstream inputFile;
  inputFile.open("input.txt", ios::in);

  int ans = 0;
  if (inputFile.is_open()) {
    string curLine;
    while (getline(inputFile, curLine)) {
      cout << curLine << endl;
      int numFront = 0;
      int numBack = 0;
      for (int i = 0; i < curLine.size(); ++i) {
        int curNum = curLine[i] - '0';
        if (curNum >= 0 && curNum <= 9) {
          numFront = curNum;
          i = curLine.size();
        }
      }
      for (int i = curLine.size() - 1; i >= 0; --i) {
        int curNum = curLine[i] - '0';
        if (curNum >= 0 && curNum <= 9) {
          numBack = curNum;
          i = -1;
        }
      }
      cout << "cur num = " << (numFront * 10 + numBack) << endl;
      ans += (numFront * 10 + numBack);
    }
    inputFile.close();
  }
  cout << "sum of all nums = " << ans << endl;
  cout << endl;
}