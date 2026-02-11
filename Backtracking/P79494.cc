#include <iostream>
#include <vector>
using namespace std;


using VE = vector<int>;
using ME = vector<VE>;
using QE = vector<ME>;
using OK = bool;


ME M;
ME fila, colu;
QE quad;


void escriu() {
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
        cout << (j ? " " : "");
        if (j == 3 or j ==  6) cout << "| ";
        cout << M[i][j];
    }
    cout << endl;
    if (i == 2 or i == 5) cout << "------+-------+------" << endl;
  }
  cout << endl;
}


void sudoku(int i, int j, bool& OK) {
  if (i == 9) {
      OK = true;
      return escriu();
  }

  if (j == 9) return sudoku(i + 1, 0, OK);

  if (M[i][j]) return sudoku(i, j + 1, OK);

  for (int x = 1; x <= 9; ++x)
    if (not fila[i][x] and not colu[j][x] and not quad[i/3][j/3][x]) {
      fila[i][x] = colu[j][x] = quad[i/3][j/3][x] = true;
      M[i][j] = x;
      sudoku(i, j + 1, OK);
      M[i][j] = 0;
      fila[i][x] = colu[j][x] = quad[i/3][j/3][x] = false;
    }
}


int main() {
  M = ME(9, VE(9));
  int t;
  cin >> t;
  char c;
  while (t--) {
    bool OK = false;
    fila = colu = ME(9, VE(10, false));
    quad = QE(3, ME(3, VE(10, false)));
    for (int i = 0; i < 9; ++i) {
       if (i == 3 or i == 6) {
            cin >> c;
            string linia;
            getline(cin, linia);
            //cout << "Eliminat linia " << linia << endl;
      }
      for (int j = 0; j < 9; ++j) {
        cin >> c;
        if (j == 3 or j == 6) cin >> c;
        //cout << "Llegint casella (" << i << ", " << j << ")" << endl;
        //cout << "Llegit " << c << endl;
        if (c != '|') {
          //cout << "Entro a l'if" << endl;
          int x = c - '0';
          M[i][j] = x;
          fila[i][x] = true;
          colu[j][x] = true;
          quad[i/3][j/3][x] = true;
        }
      }
    }
    sudoku(0, 0, OK);
    if (not OK) cout << "no solution" << endl;
    cout << "******************************" << endl;
    
  }
}
