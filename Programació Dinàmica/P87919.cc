#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using VE = vector<int>;
using MA = vector<VE>;

int min_cost = 0;


int main () {
    int n;
    while (cin >> n) {
        VE monedes(n);
        for (int i = 0; i < n; ++i) cin >> monedes[i];
        sort(monedes.begin(), monedes.end());
        int c; cin >> c;
        VE canvi (c+1, -1);
        
        int moneda_act = 0;
        for (int i = monedes[0]; i <= c; ++i) {
            if (i == monedes[moneda_act]) {
                canvi[i] = monedes[moneda_act];
                if (moneda_act < n-1) ++moneda_act;
            }
            else for (int j = moneda_act; j >= 0; --j) {
                if (i >= monedes[j] and canvi[i - monedes[j]] != -1) {
                    canvi[i] = monedes[j];
                    break;
                }
            }
        }
        if (canvi[c] == -1) cout << -1 << endl;
        else {
            cout << canvi[c]; c -= canvi[c];
            while (c > 0) {
                cout << "," << canvi[c]; c -= canvi[c];
            }
            cout << endl;
        }
    }
}
