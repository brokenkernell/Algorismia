#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using VE = vector<int>;
using ME = vector<VE>;

int n, m;
VE tasques;
VE despres;
ME abans;

void escriu() {
    for (int i = 0; i < n; ++i) cout << (i ? " " : "") << tasques[i];
    cout << endl;
}

void f (int k) {
    if (k == n) return escriu();
    for (int i = 0; i < n; ++i) {
        if (despres[i] == 0) {
            tasques[k] = i;
            --despres[i];
            
            for (int j = 0; j < abans[i].size(); ++j) --despres[abans[i][j]];
            f(k+1);
            ++despres[i];
            for (int j = 0; j < abans[i].size(); ++j) ++despres[abans[i][j]];
        }
    }
}

int main() {
    cin >> n >> m;
    tasques = VE(n);
    despres = VE(n);
    abans = ME(n, VE(0));
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        ++despres[b];
        abans[a].push_back(b);
    }
    f(0);
}
