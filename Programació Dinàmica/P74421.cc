#include <iostream>
#include <vector>
using namespace std;

using VE = vector<int>;

int n, q, b;
VE bolets, agafats;


int main() {
    for (int casos = 1; cin >> n; ++casos) {
        cout << '#' << casos << endl;
        bolets = agafats = VE(n+1, 0);
        for (int i = 1; i <= n; ++i) {
            cin >> bolets[i];
            agafats[i] = bolets[i] + agafats[i-1];
        }
        int q;
        cin >> q;
        while (q--){
            int p,c;
            cin >> p >> c;
            if (p > c) cout << agafats[p] - agafats[c-1] << endl;
            else cout << agafats[c] - agafats[p-1] << endl;
        }
    }
}
