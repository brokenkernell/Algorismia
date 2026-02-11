#include <iostream>
#include <vector>
using namespace std;

using VE = vector<int>;
using MA = vector<VE>;
using VVE = vector<MA>;

int c, v;
VE coin = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
VVE din(21, MA(581, VE(10, -1)));

int canvi (int i, int j, int k) {
    if (j < 0) return 0;
    if (din[i][j][k] != -1) return din[i][j][k];
    if (i == 1) return din[i][j][k] = (j == coin[k]);
    
    for (int l = 0; l <= k; ++l) din[i][j][k] += canvi(i-1, j- coin[k], l);
    return din[i][j][k] += 1;
}

int main () {
    int n;
    cin >> n;
    while (n--) {
        cin >> c >> v;
        int suma = 0;
        if (v <= 580) for (int i = 0; i < 10; ++i) suma += canvi (c, v, i);
        cout << suma << endl;
    }
}

