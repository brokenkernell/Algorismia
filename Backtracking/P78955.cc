#include <iostream>
#include <vector>
using namespace std;
 
typedef vector<int> VE;
typedef vector<VE> ME;
typedef vector<vector<bool> > MB;
typedef vector<MB> MTB;
 
ME S;
MB F;
MB C;
MTB Z;
bool found;
bool sonido_feo;
void escriu() {
    for (int i = 0; i < 9; ++i){
        if (i == 3 or i == 6) cout << "------+-------+------" << endl;
        bool primer = true;
        for (int j = 0; j < 9; ++j) {
            if (j == 3 or j == 6) cout << " |";
            if (primer) primer = false;
            else cout << ' ';
            cout << S[i][j] + 1;
           
        }
        cout << endl;
    }
    cout << endl;
}
 
void finder(int& x, int& y) {
    int options = 9;
    sonido_feo = false;
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            int rrj = 0;
            if (S[i][j] == -1){
                for (int k = 0; k < 9; ++k) {
                    if(F[i][k] and C[j][k] and Z[i/3][j/3][k]) ++rrj;
                }
                if (options > rrj){
                    options = rrj;
                    x = i;
                    y = j;
                }
            }
        }
    }
    if (options == 0) sonido_feo = true;
}
 
void f(int i) {
    if (found) return;
    if (i == 81) {
        found = true;
        return escriu();
    }
    int x = 0, y = 0;
    finder(x,y);
    if (sonido_feo) return;
    if (S[x][y] != -1) return f(i+1);
    for (int j = 0; j < 9; ++j){
        if(F[x][j] and C[y][j] and Z[x/3][y/3][j]){
            F[x][j] = C[y][j] = Z[x/3][y/3][j] = false;
            S[x][y] = j;
            f(i+1);
            S[x][y] = -1;
            F[x][j] = C[y][j] = Z[x/3][y/3][j] = true;
        }
    }
}
 
int main() {
    int n;
    cin >> n;
    for (int cont = 0; cont < n; ++cont){
        found = false;
        S = ME(9,VE(9,-1));
        F = C = MB(9,vector<bool>(9,true));
        Z = MTB(3,MB(3,vector<bool>(9,true)));
        char k;
        for (int i = 0; i < 9; ++i){
            for (int j = 0;j < 9; ++j){
                cin >> k;
                while (k == '-' or k == '|' or k == '+') cin >> k;
                if (k != '0') {
                    int num = k - '0' - 1;
                    S[i][j] = num;
                    F[i][num] = C[j][num] = Z[i/3][j/3][num] = false;
                }
            }
        }
        f(0);
    }
}
