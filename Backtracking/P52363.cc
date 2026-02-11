#include <iostream>
#include <vector>
using namespace std;

using VE = vector<int>;
using M = vector<VE>;

int a, b, n, total;
M maleta;
M objectes;

bool hi_cap (int i , int j, int k) {
    for (int l = 0; l < objectes[k][1]; ++l) if (maleta[i][j+l]) return false;
    return true;
}

void colocar (int i, int j, int k, int ocupat) {
    for (int l = 0; l < objectes[k][0]; ++l) {
        for (int m = 0; m < objectes[k][1]; ++m) maleta[i+l][j+m] = ocupat;
    }
}

int omplir (int i, int j) {
    if (i == a) return 1;
    if (j == b) return omplir(i+1, 0);
    if (maleta[i][j]) return omplir(i, j+1);
    int resultat = 0;
    for (int k = 0; k < n; ++k) {
        bool espai_v = (a >= objectes[k][0] + i);
        bool espai_h = (b >= objectes[k][1] + j);
        if (not objectes[k][2] and espai_v and espai_h and hi_cap(i, j, k)) {
            objectes[k][2] = 1;
            colocar(i, j, k , 1);
            resultat += omplir(i, j + objectes[k][1]);
            objectes[k][2] = 0;
            colocar(i, j, k, 0);
        }
    }
    return resultat;
}

int main () {
    for (int recompte = 1; cin >> a >> b >> n; ++recompte) {
        cout << "#" << recompte << ": ";
        maleta = M(a, VE(b, 0));
        objectes = M(n, VE(3, 0));
        for (int i = 0; i < n; ++i) cin >> objectes[i][0] >> objectes[i][1];
        cout << omplir(0,0) << endl;
        
    }
}
