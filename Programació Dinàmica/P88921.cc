#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using MA = vector<VE>;

int n, m;
MA paths;
bool great;

int f (int i, int j) {
    if (i == n or j == m) return 0;
    if (i == n-1 and j == m-1) return paths[i][j] = 1;
    if (paths[i][j] != -1) return paths[i][j];
    int valor = f(i, j+1) + f(i+1,j);
    if (valor < 1000000) return paths[i][j] = valor;
    great = true;
    return 0;
}

int main() {
    while (cin >> n >> m and n != 0) {
        paths = MA(n, VE(m, -1));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                char c;
                cin >> c;
                if (c == 'X') paths[i][j] = 0;
            }
        }
        great = false;
        int tot = f(0,0);
        if (great) cout << "!!!" << endl;
        else cout << tot << endl;
    }
}
